#!/usr/bin/env python3
# coding=utf-8

import rospy
import tf2_ros
from tf2_geometry_msgs import tf2_geometry_msgs

if __name__ == "__main__":
    # 1.初始化操作
    rospy.init_node("static_sub_node")

    # 2.tf创建监听者和缓存器
    buffer = tf2_ros.Buffer()
    sub = tf2_ros.TransformListener(buffer)

    # 3.组织要转换的坐标点
    ps = tf2_geometry_msgs.PointStamped()
    # 3-1.设置时间戳
    ps.header.stamp = rospy.Time.now()
    # 3-2.设置参考坐标系
    ps.header.frame_id = "laser"
    # 3-3.设置在坐标系中的位置
    ps.point.x = 2.0
    ps.point.y = 3.0
    ps.point.z = 5.0

    # 4.控制发布消息的频率
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        try:
            # 5.坐标点的转换
            transps = buffer.transform(ps, "base_link")
            rospy.loginfo("转换后的坐标：(%.2f,%.2f,%.2f)",
                          transps.point.x,
                          transps.point.y,
                          transps.point.z)

        except Exception as e:
            rospy.logwarn(e)

        rate.sleep()