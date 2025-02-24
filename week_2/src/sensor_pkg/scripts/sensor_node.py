#!/usr/bin/env python3
#conding = utf-8

import rospy
from sensor_msgs.msg import LaserScan

def sensor_callback(msg):
    fdist = msg.ranges[180]
    rospy.loginfo("distant:",fdist)

if __name__ == "__main__":
    rospy.init_node("sensor_node")

    sub = rospy.Subscriber("/scan",LaserScan,sensor_callback,queue_size=10)

    rospy.spin()