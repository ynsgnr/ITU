#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Transform
from geometry_msgs.msg import Twist
import tf
from tf import transformations

from math import sin,cos,atan,pi,sqrt
import time

waypoint=None


#waypoint callback
def waypoint_callback(msg): #  callback

    #***************************************
    #***          Obtain current destination
    #***************************************

    #save waypoint data for printing out in main loop
    global waypoint
    waypoint=msg;

if __name__ == '__main__':

    maxR=0.0
    maxQ=0.0
    step=0.3
    stepR=0.3
    stepTurn=1
    currentR=1.0 #starting radius
    currentQ=0.0 #starting angle
    available=True

    #setup ROS node, subscribe waypoint_cb to the topic /waypoint_cmd & publish motor commands
    rospy.init_node("crazy_driver_456")
    waypoint_subscriber = rospy.Subscriber("/waypoint_cmd", Transform, waypoint_callback) # <--- set up callback
    motor_command_publisher = rospy.Publisher("/cmd_vel_mux/input/navi", Twist, queue_size=100)
    #you could in principle also subscribe to the laser scan as is done in assignment 1.

    #setup transform cache manager
    listener = tf.TransformListener()

    #start a loop; one loop per second
    delay = rospy.Rate(5000.0); # perhaps this could be faster for a controller?
    while not rospy.is_shutdown():

        #***************************************
        #***          Obtain current robot pose
        #***************************************

        try:
            #grab the latest available transform from the odometry frame (robot's original location - usually the same as the map unless the odometry becomes inaccurate) to the robot's base.

            (translation,orientation) = listener.lookupTransform("/odom", "/base_footprint", rospy.Time(0));
        except  (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException) as e:
            print("EXCEPTION:",e)
            #if something goes wrong with this just go to bed for a second or so and wake up hopefully refreshed.
            delay.sleep()
            continue


        #***************************************
        #***          Print current robot pose
        #***************************************



        #Convert the quaternion-based orientation of the latest message to Euler representation in order to get z axis rotation
        r_xorient, r_yorient, r_zorient = transformations.euler_from_matrix(transformations.quaternion_matrix(orientation))
        robot_theta = r_zorient  # only need the z axis


        #***************************************
        #***          Print current destination
        #***************************************

        # the waypoint variable is filled in in the waypoint_callback function above, which comes from incoming messages
        # subscribed to in the .Subscriber call above.

                #Convert the quaternion-based orientation of the latest message to angle-axis in order to get the z rotation & print it.
        waypointrotq = [waypoint.rotation.x,waypoint.rotation.y,waypoint.rotation.z,waypoint.rotation.w]
        w_xorient, w_yorient, w_zorient = transformations.euler_from_matrix(transformations.quaternion_matrix(waypointrotq))
        waypoint_theta=w_zorient # only need the z axis


        #global currentR
        #global maxR
        #global currentQ
        #global maxQ
        #global step
        #global stepR

        #assumed every path starts next to the robot
        dy=waypoint.translation.y-translation[1]
        dx=waypoint.translation.x-translation[0]
        q=waypoint_theta-robot_theta #angle to turn
        q1=atan(abs(dy/dx)) #1.57079633=90degrees error correction based on coordinates
        l=sqrt(dy*dy+dx*dx)
        if (l>1):
            motor_command=Twist()
            motor_command.linear.x=0
            motor_command.angular.z=robot_theta-q1
            motor_command_publisher.publish(motor_command)
            motor_command=Twist()
            motor_command.linear.x=l
            motor_command.angular.z=0
            motor_command_publisher.publish(motor_command)
        elif(abs(currentQ)<=abs(maxQ) and currentR<=maxR):
            while(abs(currentQ)<=abs(maxQ) and currentR<=maxR):
                #apply trajectory step by step
                currentR+=stepR
                turn=(step/currentR)/2
                if(maxQ<0):
                    turn=-turn
                currentQ=currentQ+turn
                motor_command=Twist()
                motor_command.linear.x=step
                motor_command.angular.z=turn
                motor_command_publisher.publish(motor_command)
        else:
            if(abs(q)<=0.2):
                motor_command=Twist()
                motor_command.linear.x=step
                motor_command.angular.z=0
                motor_command_publisher.publish(motor_command)
            else:
                #Calculate new trejoctory
                #Print out the x,y coordinates of the transform
                print "Robot is believed to be at (x,y): (",translation[0],",",translation[1],")"
                print "Robot is believed to have orientation(theta1): (",robot_theta,")\n"
                #Print out the x,y coordinates of the latest message
                print "Current waypoint (x,y): (",waypoint.translation.x,",",waypoint.translation.y,")"
                print "Current waypoint (theta2): (",waypoint_theta,")\n"
                print "values: ",currentR,",",maxR,",",currentQ,",",maxQ,",",step,",",stepR
                currentQ=0 #starting angle
                if abs(dx)>abs(dy):
                    currentR=abs(dy) #starting radius
                else:
                    currentR=abs(dx)
                currentR=currentR*2.5 #bigger r means less error
                k=2*sin(q/2)*currentR
                maxR=dy*dy+dx*dx+k*k-2*k*(dy*sin(robot_theta)+dx*cos(robot_theta))
                print "Calculated values: q:",q," r:",currentR," dy:",dy," dx:",dx," k:",k," finalr:",maxR, "\n"
                maxR+=currentR
                maxQ=q
                #imagine a radial road with an increasing radius.
                #Calculate how much it should be increased and move step by step
                #Go increasing radial of fitted radial untill maxR with an angle of maxQ
                #If starting radius can be big enough and steps can be small enough,
                #robot would go the most optimum way in terms of the angle and the position
                #Displacements in robot's location did not calculated
                print "Max values: R:",maxR," Q:",maxQ
        delay.sleep()
        # we don't need to call spinOnce like in roscpp as callbacks happen in different threads
        #don't know how to understand that there is no more waypoints to discover so turtulebot will spin around on the last one

    print("ROS shutdown now I will also go to sleep. I hope I didn't crash. Night night.")
