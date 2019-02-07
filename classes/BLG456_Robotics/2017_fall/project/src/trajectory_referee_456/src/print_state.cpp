#include "ros/ros.h"
#include <iostream>
#include "geometry_msgs/Transform.h"
#include <tf/transform_listener.h>

int main(int argc, char **argv)
{
        //setup ROS node
        ros::init(argc, argv, "print_position");

	//setup transform cache manager
	tf::TransformListener listener;

	//start a loop; one loop per second
	ros::Rate one_hz(1);
	while(ros::ok()){
	  ros::spinOnce();

	  //the data structure that will receive the current pose
	  //the "stamped" means simply that there is time-stamp information available in the data structure's fields
	  tf::StampedTransform transform;

	  try{
	    //grab the latest available transform from the odometry frame (robot's original location - usually the same as the map unless the odometry becomes inaccurate) to the robot's base.
	    listener.lookupTransform("/odom", "/base_footprint", ros::Time(0), transform);
	  }
	  //if something goes wrong with this just go to bed for a few minutes and wake up hopefully refreshed.
	  catch (tf::TransformException ex){
	    ROS_ERROR("%s",ex.what());
	    ros::Duration(1.0).sleep();
	  }

	  //Print out the x,y coordinates of the transform
	  std::cout<<"Robot position (x,y): ("<<transform.getOrigin().x()<<","<<transform.getOrigin().y()<<")"<<std::endl;

	  //Convert the quaternion-based orientation of the latest message to angle-axis in order to get the z rotation & print it.
	  tf::Vector3 axis=transform.getRotation().getAxis();
	  double angle=transform.getRotation().getAngle();
	  double theta=angle*axis[2];
	  std::cout<<"Robot orientation (theta): ("<<theta<<")"<<std::endl<<std::endl;

	  one_hz.sleep();
	}
        return 0;
}
