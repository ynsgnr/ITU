#!/usr/bin/env python

import rospy
import sys

from geometry_msgs.msg import Twist
from geometry_msgs.msg import Transform
from nav_msgs.msg import OccupancyGrid

import tf
from tf import transformations

#BELOW CODE WRITTEN BY YUNUS GÜNGÖR FOR BLG456 PROJECT (2017)
#
# This module is written as a part of drone project
# by team K1000 of BLG456E Fall 2017 Class in Istanbul Technical University
#

#This modules assumes mapping done correctly but uses 2D mapping
#expected incoming object vector is relative to the drone's camera
#For Example:
#   --------------------
#   |                   |
#   |              *    |
#   |         C         |
#   |                   |
#   |___________________|
#
#   C is center and * is the object, expected vector is (3,2) because C considered as origin
#   This vector can be send to the "/incoming" topic
#
#   Example command:
#    rostopic pub /incoming geometry_msgs/Transform '{translation: {x:0.1, y: 0, z: 0}, rotation: {x: 1, y: 1, z: 1}}'
#    closer to the center, quicker the movement
#
#
#   Path to be followed should be send to the "/waypoint_cmd" topic as transform object one by one (Just like assignment 2 in robotics)
#

waypoint=None
slamMap=None

incomingVector=None
control=True

robotX=0
robotY=0
robotZ=0

from nav_msgs.msg import OccupancyGrid

import math
import time

def map_callback(data):
    global slamMap
    slamMap=data

def avoid_object(msg):

    global control
    global incomingVector

    k=0.1
    moveK=5
    size=2
    error=False
    objectDetected=False
    control=False
    #Send commands to avoid incoming object trajectory

    #rapid move to avoid objects

    print "Incoming object!"

    if(msg.translation.x==0):
        rx=0
    else:
        rx=1/msg.translation.x*k

    if(msg.translation.y==0):
        ry=0
    else:
        ry=1/msg.translation.y*k

    rz=0

    #check map:

    if slamMap is not None:
        if(rx<0):
            xMax = round((robotX-slamMap.info.origin.position.x+size)/slamMap.info.resolution)
            xMin = round((robotX-slamMap.info.origin.position.x-rx*moveK-size)/slamMap.info.resolution)
        else:
            xMax = round((robotX-slamMap.info.origin.position.x+rx*moveK+size)/slamMap.info.resolution)
            xMin = round((robotX-slamMap.info.origin.position.x-size)/slamMap.info.resolution)

        if(ry<0):
            yMax = round((robotY-slamMap.info.origin.position.y+size)/slamMap.info.resolution)
            yMin = round((robotY-slamMap.info.origin.position.y-rx*moveK-size)/slamMap.info.resolution)
        else:
            yMax = round((robotY-slamMap.info.origin.position.y+rx*moveK+size)/slamMap.info.resolution)
            yMin = round((robotY-slamMap.info.origin.position.y-size)/slamMap.info.resolution)


        xRob = round((robotX-slamMap.info.origin.position.x)/slamMap.info.resolution)
        yRob = round((robotY-slamMap.info.origin.position.y)/slamMap.info.resolution)

        print "Robot coordinates: ", robotX, "-", robotY, "-", robotZ
        print "Map data: ", slamMap.info.width, "-", slamMap.info.height, "-", slamMap.info.resolution, "-", slamMap.info.origin.position.x, "-", slamMap.info.origin.position.y
        print "Checking map: ", xMax, "-", xMin, "-", yMax, "-", yMin, " Robot on map: ", int(xRob), "-", int(yRob)


        for y in range(int(yMin),int(yMax),1):
            for x in range(int(xMin),int(xMax),1):
                index = x+y*slamMap.info.width
                if abs(xRob-x)<1 and abs(yRob-y)<1:
                    if slamMap.data[index] > 90:
                        error = True
                    #sys.stdout.write('R')
                elif slamMap.data[index] > 90:
                    ## This square is occupied
                    objectDetected = True
                    #sys.stdout.write('X')
                #elif slamMap.data[index] >= 0:
                    ## This square is unoccupied
                    #sys.stdout.write(" ")
                #else:
                    #sys.stdout.write('?')
            #sys.stdout.write('\n')


    motor_command=Twist()

    if not error and objectDetected:
        print "Object detected but can not rapid move"
        rx=0
        ry=0
        if robotZ<2:
            print "at least go up"
            rz=-k*5 #go up
        else:
            print "at least go down"
            rz=robotZ*3 #go down


    motor_command.linear.x = -rx
    motor_command.linear.y = -ry
    motor_command.linear.z = -rz

    motor_command_publisher.publish(motor_command)

    #disable sensor

    rospy.sleep(0.6)

    #enable sensor

    motor_command.linear.x = rx*2
    motor_command.linear.y = ry*2
    motor_command.linear.z = rz*2

    motor_command_publisher.publish(motor_command)

    control=True


    incomingVector=msg
    print(msg)

def waypoint_callback(msg):
    global waypoint
    waypoint=msg;

def follower_node():

    rospy.init_node('follower')

    global robotX
    global robotY
    global robotZ

    global motor_command_publisher
    motor_command_publisher = rospy.Publisher('/cmd_vel', Twist, queue_size = 10)

    waypoint_subscriber = rospy.Subscriber("/waypoint_cmd", Transform, waypoint_callback)

    action_subscriber = rospy.Subscriber("/incoming", Transform, avoid_object)

    map_subscriber = rospy.Subscriber("/map", OccupancyGrid, map_callback, queue_size = 1000)

    listener = tf.TransformListener()
    step=1
    size=0.7

    dx=0
    dy=0
    dz=0

    print "Starting, dont forget to enable motors"

    delay = rospy.Rate(50.0);
    while not rospy.is_shutdown():
        motor_command = Twist()
        objectDetected=False
        error = False
        stopped = False
        if control:
            try:
                #grab the latest available transform from the odometry frame (robot's original location - usually the same as the map unless the odometry becomes inaccurate) to the robot's base.
                (translationZ,orientationZ) = listener.lookupTransform("/base_link", "/base_footprint", rospy.Time(0));
            except  (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException) as e:
                print("EXCEPTION:",e)
                #if something goes wrong with this just go to bed for a second or so and wake up hopefully refreshed.
                delay.sleep()
                continue

            try:
                #grab the latest available transform from the odometry frame (robot's original location - usually the same as the map unless the odometry becomes inaccurate) to the robot's base.
                (translation,orientation) = listener.lookupTransform("/world", "/base_footprint", rospy.Time(0));
            except  (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException) as e:
                print("EXCEPTION:",e)
                delay.sleep()
                continue

            #print "\n---------------------\ntranslation: ", translation, "\norientation: ", orientation, "\nwaypoint:\n", waypoint

            robotX=translation[0]
            robotY=translation[1]
            robotZ=translationZ[2]
            print "Robot coordinates: ", robotX, "-", robotY, "-", robotZ

            if slamMap is not None:
                xMax = round((robotX-slamMap.info.origin.position.x+size)/slamMap.info.resolution)
                yMax = round((robotY-slamMap.info.origin.position.y+size)/slamMap.info.resolution)
                xMin = round((robotX-slamMap.info.origin.position.x-size)/slamMap.info.resolution)
                yMin = round((robotY-slamMap.info.origin.position.y-size)/slamMap.info.resolution)
                xRob = round((robotX-slamMap.info.origin.position.x)/slamMap.info.resolution)
                yRob = round((robotY-slamMap.info.origin.position.y)/slamMap.info.resolution)

                print "Map data: ", slamMap.info.width, "-", slamMap.info.height, "-", slamMap.info.resolution, "-", slamMap.info.origin.position.x, "-", slamMap.info.origin.position.y
                print "Checking map: ", xMax, "-", xMin, "-", yMax, "-", yMin, " Robot on map: ", int(xRob), "-", int(yRob)

                #sys.stdout.write('\n')

                for y in range(int(yMin),int(yMax),1):
                    for x in range(int(xMin),int(xMax),1):
                        index = x+y*slamMap.info.width
                        if abs(xRob-x)<1 and abs(yRob-y)<1:
                            if slamMap.data[index] > 90:
                                error = True
                            #sys.stdout.write('R')
                        elif slamMap.data[index] > 90:
                            ## This square is occupied
                            objectDetected = True
                            #sys.stdout.write('X')
                        #elif slamMap.data[index] >= 0:
                            ## This square is unoccupied
                            #sys.stdout.write(" ")
                        #else:
                            #sys.stdout.write('?')
                    #sys.stdout.write('\n')
            else:
                print "Map data not found! Check if slam works"


            if not error and objectDetected:
                print("Object detected, stop!")
                if not stopped and dx!=0 and dy!=0 and dz!=0:
                    motor_command.linear.x = -dx
                    motor_command.linear.y = -dy
                    motor_command.linear.z = -dz

                    #print "command!\n", motor_command.linear.x, "-", motor_command.linear.y, "-", motor_command.linear.z, "-k: ", k

                    motor_command_publisher.publish(motor_command)
                stopped=True
            else:
                if(abs(robotZ)<0.3): #prevent collisions
                     motor_command.linear.z = 0.2
                     motor_command_publisher.publish(motor_command)
                     rospy.sleep(0.2)


                dx=waypoint.translation.x-robotX
                dy=waypoint.translation.y-robotY
                dz=waypoint.translation.z+robotZ#base link has negative z

                #print "moving!\n", dx, "-", dy, "-", dz

                k=1
                if(abs(dx)>step or abs(dy)>step or abs(dz)>step):
                    maxd = max(abs(dx),abs(dy),abs(dz))
                    k = step / maxd
                    dx = dx*k
                    dy = dy*k
                    dz = dz*k

                motor_command.linear.x = dx
                motor_command.linear.y = dy
                motor_command.linear.z = dz

                #print "command!\n", motor_command.linear.x, "-", motor_command.linear.y, "-", motor_command.linear.z, "-k: ", k

                motor_command_publisher.publish(motor_command)


if __name__ == '__main__':
    follower_node()
