cmake_minimum_required(VERSION 2.8.3)
project(a1_456_answer)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
)

add_executable(explorer_node_a1_456_cpp src/explorer_node_a1_456_cpp.cpp)

target_link_libraries(explorer_node_a1_456_cpp ${catkin_LIBRARIES})

