/*
 * referee_node_a1_456.cpp
 *
 * BLG456E Assignment 1 referee
 *
 */
#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "gazebo_msgs/GetModelState.h"
#include "nav_msgs/GetMap.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <tf/transform_listener.h>
#include <sys/stat.h>
#include <unistd.h>
#include "eigen_conversions/eigen_msg.h"

bool close_when_finished_snapshots=false;
bool append_to_output_file=false;

double see_dist = 1.0;
double see_angular_interval_degrees = 1.0;
double see_interval_metres = 0.01;
double see_FOV_degrees = 90;

std::string mapdir_base = "a1_456_results_maps";

ros::Duration spinfreq(0.1);

ros::ServiceClient ground_truth_pose_getter;
ros::ServiceClient ground_truth_map_getter;
ros::Publisher map_publisher;

nav_msgs::OccupancyGrid collision_map;
nav_msgs::OccupancyGrid explored_map;

// double times_to_snapshot[] = {10,60,120,240,600,1200};
// int num_times_to_snapshot = 6;
double times_to_snapshot[] = {10,20,30,40};
int num_times_to_snapshot = 4;

double wait_seconds_at_start=5;

int main(int argc, char **argv)
{

    int return_status=0;

    ros::init(argc, argv, "referee_node");
    std::string run_id,run_no;

//     tf::TransformListener listener(ros::Duration(10.0));
    ros::NodeHandle n;

    if(n.hasParam("/a1_run_id"))
        n.getParam("/a1_run_id",run_id);
    else
        run_id="XX";

    if(n.hasParam("/a1_run_no"))
        n.getParam("/a1_run_no",run_no);
    else
        run_no="YY";

    ground_truth_pose_getter = n.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");
    nav_msgs::GetMap ground_truth_map_getter_data;

    ground_truth_map_getter = n.serviceClient<nav_msgs::GetMap>("/dynamic_map");

    gazebo_msgs::GetModelState ground_truth_pose_getter_data;
    ground_truth_pose_getter_data.request.model_name="mobile_base";
    ground_truth_pose_getter_data.request.relative_entity_name="world";

    map_publisher=n.advertise<nav_msgs::OccupancyGrid>("/ground_truth_map",100);

    bool first=true;
    ros::Time timenow;
    ros::Time starttime;
    ros::WallTime startwalltime;
    ros::WallTime walltime;
    Eigen::Affine3d prev_ground_truth_pose;

    std::fstream results;
    if(append_to_output_file)
      results.open((std::string(getenv("HOME")) + "/" + "a1_456_results.csv").c_str(), std::ios::out | std::ios::app);
    else
      results.open((std::string(getenv("HOME")) + "/" + "a1_456_results.csv").c_str(), std::ios::out | std::ios::trunc);
    if(!results.is_open()) {
        std::cout<<"COULD NOT OPEN RESULTS FILE"<<std::endl;
        exit(1);
    }

    std::string mapdir_root = std::string(getenv("HOME")) + "/" + mapdir_base;
    mkdir(mapdir_root.c_str(),  S_IRWXU );
    std::stringstream ss;
    ss<<mapdir_root<<"/"<<run_id;
    mkdir(ss.str().c_str(), S_IRWXU );
    ss<<"/"<<run_no;
    mkdir(ss.str().c_str(), S_IRWXU );
    std::string mapdir   = ss.str();

    int uncovered_grid_squares=0;
    int counter=0;
    double distance_travelled=0;
    int num_snapshotted=0;
    usleep(wait_seconds_at_start*1000000/2); //saves some race conditions

    while(ros::ok() ) {

        results.flush();
        spinfreq.sleep();
        ros::spinOnce();

//         std::cout<<"DOING"<<std::endl;

        if(first) {
            first=false;
            usleep(wait_seconds_at_start*1000000/2); //saves some race conditions
            starttime=ros::Time::now();
            startwalltime=ros::WallTime::now();
            ground_truth_map_getter.call(ground_truth_map_getter_data);
            collision_map=ground_truth_map_getter_data.response.map;
            explored_map=collision_map;
            for(int i=0; i<explored_map.data.size(); i++) {
                if(explored_map.data[i]==0)explored_map.data[i]=-1; //set empty to unexplored
            }
            ground_truth_pose_getter.call(ground_truth_pose_getter_data);
            tf::poseMsgToEigen(ground_truth_pose_getter_data.response.pose,prev_ground_truth_pose);
            continue;
        }
        ground_truth_pose_getter.call(ground_truth_pose_getter_data);
        Eigen::Affine3d ground_truth_pose;
        tf::poseMsgToEigen(ground_truth_pose_getter_data.response.pose,ground_truth_pose);
        Eigen::Affine3d ground_truth_pose_inv=ground_truth_pose.inverse();

        for(double angle=-see_FOV_degrees/2; angle<=see_FOV_degrees/2; angle+=see_angular_interval_degrees) {
            double angle_rad = (M_PI*angle)/180;
            double sinA = sin(angle_rad);
            double cosA = cos(angle_rad);
            bool coll=false;
            for(double extent=0; extent<see_dist && !coll; extent+=see_interval_metres) {
                double x_extent_r=extent*cosA;
                double y_extent_r=extent*sinA;
                Eigen::Vector4d check_r(x_extent_r,y_extent_r,0,1);
                Eigen::Vector4d check_w =  ground_truth_pose_inv * check_r;
                int x_check_w_ind = (check_w[0] - explored_map.info.origin.position.x)/explored_map.info.resolution;
                int y_check_w_ind = (check_w[1] - explored_map.info.origin.position.y)/explored_map.info.resolution;
                if(x_check_w_ind>=0&&x_check_w_ind<explored_map.info.width) {
                    if(y_check_w_ind>=0&&y_check_w_ind<explored_map.info.height) {
                        int check_ind = x_check_w_ind + y_check_w_ind * explored_map.info.width;
                        if(explored_map.data[check_ind]<0){
                          explored_map.data[check_ind]=0;
                          uncovered_grid_squares++;
                        }
                        else if(explored_map.data[check_ind]>50) {
                            coll=true;
                            break;
                        }
                    }

                }

            }
        }
        map_publisher.publish<nav_msgs::OccupancyGrid>(explored_map);
        timenow=ros::Time::now();
        walltime=ros::WallTime::now();
        ros::Duration elapsed=timenow-starttime;

        std::stringstream resultstring;
//         resultstring<<run_id<<","<<run_no<<","<<counter<<","<<std::setprecision(8)<<elapsed.toSec()<<","<<discoveredArea<<","<<unknownArea<<","<<occupiedArea;
        resultstring<<run_id<<","<<run_no<<","<<counter<<","<<std::setprecision(8)<<elapsed.toSec()<<","<<uncovered_grid_squares;

//         std::cout<<"Time elapsed (s): "<<elapsed.toSec()<<" Discovered Area: "<<discoveredArea<<" Unknown Area: "<<unknownArea<<" Occupied Area: "<<occupiedArea<<std::endl;
        if(counter%20==0){
            std::cout<<"Ground truth pose: "<<ground_truth_pose.matrix()<<std::endl;
            std::cout<<std::endl;
            std::cout<<"# uncovered squares: "<<uncovered_grid_squares<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
        }

        if(walltime-startwalltime>ros::WallDuration(40.0*60)) {
            std::cout<<resultstring.str()<<std::endl;
            std::cout<<"This is taking too long in the real world"<<std::endl;
            results<<resultstring.str()<<",This took forever (>40 min) so I gave up."<<std::endl;
            break;
        }
        else {
            distance_travelled=(ground_truth_pose.translation()-prev_ground_truth_pose.translation()).norm();
            if(distance_travelled>50.0) {
                std::cout<<"Robot flew away."<<std::endl;
                results<<resultstring.str()<<",Robot flew away."<<std::endl;
                return_status=1;
                break;
            }
            else if(num_snapshotted<num_times_to_snapshot&& elapsed.toSec() >= times_to_snapshot[num_snapshotted]) {
                std::ostringstream oss;
                oss<<"rosrun map_server map_saver -f "<<mapdir<<"/snapshot"<<times_to_snapshot[num_snapshotted]<<" map:=/ground_truth_map &";
                system(oss.str().c_str());
                num_snapshotted++;
                results<<resultstring.str()<<",Normal snapshot."<<std::endl;
            }
            else if(num_snapshotted>=num_times_to_snapshot && close_when_finished_snapshots) {
                results<<resultstring.str()<<",Finished run."<<std::endl;
                std::cout<<"Finished run with "<<elapsed.toSec()<<" seconds elapsed"<<std::endl;
                std::cout<<"Waiting 10 seconds to close referee - waiting or cleaup."<<std::endl;
                usleep(10000000);
                break;
            }
            else {
                //continuing on for fun
            }
            counter+=1;
        }
        prev_ground_truth_pose=ground_truth_pose;

    }

    std::cout<<"Referee is closing, thanks."<<std::endl;

    results.flush();
    results.close();


    return return_status;
}

