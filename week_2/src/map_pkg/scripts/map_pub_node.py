#!/usr/bin/env python3
#conding=utf-8

import rospy
from nav_msgs.msg import OccupancyGrid

if __name__ == "__main__":
    rospy.init_node("map_pub_node")
    rate = rospy.Rate(10)

    # 获取发布者
    pub = rospy.Publisher("/map",OccupancyGrid,queue_size=10)
    # 定义地图消息包
    msg = OccupancyGrid()
    msg.header.frame_id = "map"
    msg.header.stamp = rospy.Time.now()
    # 地图起点与坐标轴偏移量
    msg.info.origin.position.x = 0
    msg.info.origin.position.y = 0
    # 地图分辨率
    msg.info.resolution = 1.0
    # 地图大小
    msg.info.width = 4
    msg.info.height = 2
    # 栅格赋值
    msg.data = [0]*4*2
    msg.data[0] = 100
    msg.data[1] = 100
    msg.data[2] = 0
    msg.data[3] = -1

    # 消息发布
    while not rospy.is_shutdown():
        pub.publish(msg)
        rate.sleep()
        
