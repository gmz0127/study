#!/usr/bin/env python3
#conding=utf-8

import rospy
from geometry_msgs.msg import Twist

if __name__ == "__main__":

    rospy.init_node("vel_node")

    pub = rospy.Publisher ("/cmd_vel",Twist,queue_size=10)
    r = rospy.Rate(30)

    vel_msg = Twist()
    vel_msg.linear.x = 0.1

    while not rospy.is_shutdown():
        pub.publish(vel_msg)
        r.sleep()