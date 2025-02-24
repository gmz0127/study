#!/usr/bin/env python3
#encoding=utf-8

import rospy
from turtlesim.msg import Pose
import tf2_ros
from geometry_msgs.msg import TransformStamped
import tf

def dopose(pose):
    # 1.创建动态坐标系信息对象
    pub = tf2_ros.TransformBroadcaster()

    # 2.组织坐标系相对位置信息
    # 获取信息对象
    tfs = TransformStamped()

    # 编辑表头
    tfs.header.frame_id = "world"
    tfs.header.stamp = rospy.Time.now()

    # 编辑子坐标
    tfs.child_frame_id = "turtlesim"

    # 编辑x,y,z偏移量
    tfs.transform.translation.x = pose.x
    tfs.transform.translation.y = pose.y
    tfs.transform.translation.z = 0

    # 欧拉角转四元数
    qnt = tf.transformations.quaternion_from_euler(0,0,pose.theta)
    tfs.transform.rotation.x = qnt[0]
    tfs.transform.rotation.y = qnt[1]
    tfs.transform.rotation.z = qnt[2]
    tfs.transform.rotation.w = qnt[3]

    # 信息发布
    pub.sendTransform(tfs)


if __name__ == "__main__":
    rospy.init_node("domatic_pub")

    # 1.创建订阅者，订阅/turtle1/pose话题
    sub = rospy.Subscriber("/turtle1/pose",Pose,dopose,queue_size=100)

    # 2.spin
    rospy.spin()