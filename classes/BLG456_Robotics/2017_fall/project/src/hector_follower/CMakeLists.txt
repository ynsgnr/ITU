cmake_minimum_required(VERSION 2.8.3)
project(hector_follower)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
)
