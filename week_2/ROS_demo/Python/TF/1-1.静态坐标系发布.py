#!/usr/bin/env python3
# conding=utf-8

import rospy
import tf2_ros
from geometry_msgs.msg import TransformStamped
import tf

if __name__ == "__main__":
    # 初始化操作
    rospy.init_node("static_pub_node")

    # 获取发布对象
    pub = tf2_ros.StaticTransformBroadcaster()

    # 组织发布信息
    msg = TransformStamped()
    # 父坐标系
    msg.header.frame_id = "base_link"
    # 时间戳
    msg.header.stamp = rospy.Time.now()

    # 子坐标系
    msg.child_frame_id = "laser"

    # xyz偏移量
    msg.transform.tanslation.x = 2.0
    msg.transform.tanslation.y = 0.0
    msg.transform.tanslation.z = 0.5

    # 欧拉数与四元数转换
    # python中获取四元数对象是通过tf下的transformation.quation_from_euler函数，直接传入欧拉角
    # 传入欧拉角获取四元数对象
    qnt = tf.transformations.quation_from_euler(0, 0, 0)
    # 获取对应的四元数进行赋值操作
    msg.transform.rotation.x = qnt[0]
    msg.transform.rotation.y = qnt[1]
    msg.transform.rotation.z = qnt[2]
    msg.transform.rotation.w = qnt[3]

    # 发布数据
    pub.sendTransform(msg)

    rospy.spin()
