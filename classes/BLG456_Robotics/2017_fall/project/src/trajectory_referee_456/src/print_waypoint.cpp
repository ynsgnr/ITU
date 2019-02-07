#include "ros/ros.h"
#include <iostream>
#include "geometry_msgs/Transform.h"
#include <tf/tf.h>

//node subscriber
ros::Subscriber sub_; 
//contains waypoint data
geometry_msgs::Transform curr_waypoint;

//waypoint callback
void waypoint_cb(const geometry_msgs::Transform::ConstPtr& msg)
{                 
    //save waypoint data for printing out in main loop
    curr_waypoint=*msg;
}

int main(int argc, char **argv)
{       
        //setup ROS node & subscribe waypoint_cb to the topic /waypoint_cmd
        ros::init(argc, argv, "print_waypoint");
        ros::NodeHandle n; 
        sub_ = n.subscribe("/waypoint_cmd", 1000,waypoint_cb); 
	
	//start a loop; one loop per second
	ros::Rate one_hz(1);
	while(ros::ok()){
	  ros::spinOnce();

	  //Print out the x,y coordinates of the latest message
	  std::cout<<"Current waypoint (x,y): ("<<curr_waypoint.translation.x<<","<<curr_waypoint.translation.y<<")"<<std::endl;
	  
	  //Convert the quaternion-based orientation of the latest message to angle-axis in order to get the z rotation & print it.
	  tf::Quaternion quat(curr_waypoint.rotation.x,curr_waypoint.rotation.y,curr_waypoint.rotation.z,curr_waypoint.rotation.w);
	  tf::Vector3 axis=quat.getAxis();
	  double angle=quat.getAngle();
	  double theta=angle*axis[2];
	  std::cout<<"Current waypoint (theta): ("<<theta<<")"<<std::endl<<std::endl;
	  
	  one_hz.sleep();
	}
        return 0;
}
