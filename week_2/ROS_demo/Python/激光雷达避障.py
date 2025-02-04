#!/usr/bin/env python3
# conding = utf-8

import rospy
from sensor_msgs.msg import LaserScan
from geometry_msg.msg import Twist

# 旋转时间
count = 0;


# 回调函数
def LaserScanCallBack(msg):
    global vel_pub
    global count
    # 获取前方障碍距离信息
    float
    fdist = msg.ranges[180]
    rospy.loginfo("前方障碍距离：%f米", fdist)
    # 速度控制消息包
    vel_msg = Twist()

    if count > 0:
        count -= 1
        return

    if fdist < 1.5:
        count = 50
        vel_msg.angular.z = 0.3
    else:
        vel_msg.linear.x = 0.5

    # 发布速度消息
    vel_pub.publish(vel_msg)


if __name__ == "__main__":
    # 初始化
    rospy.init_node("ladir_behavior_node")

    # 订阅者
    ladir_sub = rospy.Subscriber("/scan", LaserScan, LaserScanCallBack, queue_size=10)

    # 发布者
    vel_pub = rospy.Publisher("/cmd_vel", queue_size=10)