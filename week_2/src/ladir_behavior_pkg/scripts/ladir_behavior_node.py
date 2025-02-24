#!/usr/bin/env python3
#conding = utf-8

import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

count = 0
def LaserScanCallBack(msg):
    global vel_pub
    global count

    fdist = msg.ranges[180]
    rospy.loginfo("distant:%f",fdist)

    vel_msg = Twist()
    if count > 0:
        count -= 1
        return

    if fdist < 1.5:
        vel_msg.angular.z = 0.3
        count = 50
    else:
        vel_msg.linear.x = 0.1
    
    vel_pub.publish(vel_msg)

if __name__ == "__main__":
    rospy.init_node("ladir_behavior_node")

    ladir_sub = rospy.Subscriber("/scan",LaserScan,LaserScanCallBack,queue_size=10)
    vel_pub = rospy.Publisher("/cmd_vel",Twist,queue_size=10)
    
    rospy.spin()