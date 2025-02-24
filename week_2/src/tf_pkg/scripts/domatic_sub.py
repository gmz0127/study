#!/usr/bin/env python3
#encoding=utf-8

import rospy
import tf2_ros
from tf2_geometry_msgs import tf2_geometry_msgs

if __name__ =="__main__":
    rospy.init_node("domatic_sub")

    # 1.创建坐标系监听对象
    buffer = tf2_ros.Buffer()
    sub = tf2_ros.TransformListener(buffer)

    # 2.组织坐标点信息
    ps = tf2_geometry_msgs.PointStamped()

    ps.header.frame_id = "turtlesim"
    ps.header.stamp = rospy.Time(0.0)

    ps.point.x = 2.0
    ps.point.y = 2.0
    ps.point.z = 2.0

    # 3.坐标变化发布频率
    rate = rospy.Rate(1)
    rospy.sleep(2)

    while not rospy.is_shutdown():
        # 4.进行坐标变化
        ps_out = buffer.transform(ps,"world")

        # 5.展示变换后的坐标
        rospy.loginfo("坐标变换后(%.2f,%.2f,%.2f),参考坐标系为%s",
                      ps_out.point.x,
                      ps_out.point.y,
                      ps_out.point.z,
                      ps_out.header.frame_id)
        rospy.loginfo("坐标变换前(%.2f,%.2f,%.2f),参考坐标系为%s",
                      ps.point.x,
                      ps.point.y,
                      ps.point.z,
                      ps.header.frame_id)
        
        rate.sleep()
        
