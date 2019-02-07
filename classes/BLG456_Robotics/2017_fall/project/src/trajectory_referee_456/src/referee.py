#!/usr/bin/env python
import math

PKG_NAME="trajectory_referee_456"

XY_CLOSENESS_THRESH=0.2
COSTHETA_CLOSENESS_THRESH=0.5-0.5*math.cos(math.pi/4)
#TIMEOUT=100

#PERTURBATIONS_SIZE=1
#PERTURBATIONS_SIZE=0.01
PERTURBATIONS_SIZE=0
Z_INDEX=2

import roslib
roslib.load_manifest(PKG_NAME)
import rospy
import geometry_msgs
import geometry_msgs.msg
import gazebo_msgs
import gazebo_msgs.srv
import gazebo_msgs.msg
import visualization_msgs
import visualization_msgs.msg
import trajectory_msgs
import trajectory_msgs.msg
#import arm_navigation_msgs
#import arm_navigation_msgs.msg
import sys
import time
import tf
import tf.transformations
import signal
import pickle
import random

import roslib.packages

if len(sys.argv)<3:
  print """Please give arguments:
            First argument: which route? One of route1, route2, route3 or route4.
            Second argument: displacement following only (dis) or displacement and orientation (dor).
            e.g.:
            rosrun trajectory_referee_456 route1 dis
            """

if sys.argv[1] not in ["route1","route2","route3","route4"]:
  print "Please give one of route1, route2, route3 or route4 for first argument."
  sys.exit(1)

if sys.argv[2] not in ["dis","dor"]:
  print "Please give one of dis or dor for second argument."
  sys.exit(1)

orientation_check_on = False
if sys.argv[2].lower()=="dor":orientation_check_on=True

routefname = roslib.packages.get_pkg_dir(PKG_NAME)+"/routes/"+sys.argv[1]+".pkl"
with open(routefname,"r") as f:
  route_raw=pickle.load(f)

route=trajectory_msgs.msg.MultiDOFJointTrajectory()

route.joint_names=["base_link"]
route.points=[]

marker_array=visualization_msgs.msg.MarkerArray()
marker_cntr=0
for ritem in route_raw:
  route_point=trajectory_msgs.msg.MultiDOFJointTrajectoryPoint()
  route_point.time_from_start=rospy.Duration(ritem[0])

  # BELOW CODE EDITED BY YUNUS GÜNGÖR FOR BLG456 PROJECT IN ITU (2017)
  transform=geometry_msgs.msg.Transform()
  transform.translation.x=ritem[1]
  transform.translation.y=ritem[2]
  transform.translation.z=abs(ritem[2])+0.3
  q=tf.transformations.quaternion_from_euler(0,0,ritem[3])
  transform.rotation.z=q[2]
  transform.rotation.w=q[3]
  transform.rotation.x=q[0]
  transform.rotation.y=q[1]

  route_point.transforms.append(transform)

  route.points.append(route_point)

  marker=visualization_msgs.msg.Marker()
  marker.header.frame_id="world"
  marker.id=marker_cntr
  marker_cntr=marker_cntr+1
  marker.type=visualization_msgs.msg.Marker.ARROW
  marker.pose.position.x=ritem[1]
  marker.pose.position.y=ritem[2]
  marker.pose.position.z=abs(ritem[2])+0.3
  marker.pose.orientation=transform.rotation
  marker_array.markers.append(marker)
  marker.scale.x=0.2
  marker.scale.y=0.02
  marker.scale.z=0.02
  marker.color.r=1.0
  marker.color.g=(1.0*marker_cntr)/len(route_raw)
  marker.color.b=1.0-(1.0*marker_cntr)/len(route_raw)
  marker.color.a=1.0

rospy.init_node('referee')
rospy.wait_for_service("/gazebo/get_model_state")
rospy.wait_for_service("/gazebo/apply_body_wrench")
route_pub = rospy.Publisher('/route_cmd', trajectory_msgs.msg.MultiDOFJointTrajectory,queue_size=1)
waypoint_pub = rospy.Publisher('/waypoint_cmd',geometry_msgs.msg.Transform,queue_size=1)
marker_pub = rospy.Publisher('/visualization_marker_array', visualization_msgs.msg.MarkerArray,queue_size=1)
get_state=rospy.ServiceProxy("/gazebo/get_model_state",gazebo_msgs.srv.GetModelState)
apply_wrench=rospy.ServiceProxy("/gazebo/apply_body_wrench",gazebo_msgs.srv.ApplyBodyWrench)

r=rospy.Rate(100)

print "Publishing route..."
if not rospy.is_shutdown():
  r.sleep()
  route_pub.publish(route)
  waypoint_pub.publish(route.points[0].transforms[0])
  print "Published route. Now it's over to you (will publish it again occasionally & also publish individual waypoints)."
else:
  print "ROS seems to have died - oh well too bad - probably the divil - bye."
  sys.exit(0)

start_time=time.time()
route_cntr=0
cumulative_dur_error=0
loop_cntr=0

while route_cntr<len(route_raw) and not rospy.is_shutdown():

  loop_cntr=loop_cntr+1

  marker_pub.publish(marker_array)

  nowtime=time.time()
  tdiff=nowtime-start_time
  sget=get_state("quadrotor","world")
  x=sget.pose.position.x
  y=sget.pose.position.y
  z=sget.pose.position.z

  this_point=route_raw[route_cntr]

  print "Robot is at ", x, "-", y, "-", z, "\nPoint is at: ", this_point[1], "-", this_point[2], "-", this_point[3]

  o=sget.pose.orientation
  q=[o.x,o.y,o.z,o.w]
  ga,gb,theta=tf.transformations.euler_from_quaternion(q)

  #publish waypoints constantly
  wp=route.points[route_cntr].transforms[0]
  waypoint_pub.publish(wp)

  #publish route again every second, just in case it was missed the first time.
  if loop_cntr%100 == 0:
    route_pub.publish(route)

  #add some fun and yet mean noise
  if loop_cntr%20==0 and PERTURBATIONS_SIZE>0:
    wrench=geometry_msgs.msg.Wrench()

    wrench.force.x=(random.random()-0.5)*PERTURBATIONS_SIZE
    wrench.force.y=(random.random()-0.5)*PERTURBATIONS_SIZE
    wrench.force.z=(random.random()-0.5)*PERTURBATIONS_SIZE
    wrench.torque.x=(random.random()-0.5)*PERTURBATIONS_SIZE
    wrench.torque.y=(random.random()-0.5)*PERTURBATIONS_SIZE
    wrench.torque.z=(random.random()-0.5)*PERTURBATIONS_SIZE
    wret=apply_wrench(body_name="base_link",wrench=wrench,duration=rospy.Duration(1.0/100))


  linear_error=math.sqrt((x-this_point[1])**2+(y-this_point[2])**2+(z-abs(this_point[2])-0.3)**2)
  print "Linear error: ", linear_error
  angle_error=0.5-0.5*math.cos((theta-this_point[3]))

  duration_error=tdiff-this_point[0]

  if linear_error<=XY_CLOSENESS_THRESH and (not orientation_check_on or angle_error<=COSTHETA_CLOSENESS_THRESH):

    print "ACHIEVED WAYPOINT ",route_cntr, "with lateness of",duration_error
    print "  (linear error",linear_error," angle_error",angle_error,")"
    cumulative_dur_error=cumulative_dur_error+duration_error
    marker_array.markers[route_cntr].color.a=0.35
    route_cntr=route_cntr+1

  r.sleep()

print "  "
print "YOUR CUMULATIVE LATENESS IS",cumulative_dur_error,"seconds."
