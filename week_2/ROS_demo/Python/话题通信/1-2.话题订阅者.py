#!/usr/bin/env python3
# encoding=utf-8

import rospy
from std_msgs.msg import String


# 回调函数
def hello_callback(msg):
    rospy.loginfo("接收到的消息：%s", msg.data)


if __name__ == "__main__":
    # 1.初始化
    rospy.init_node("hello_pub_node")

    # 2.获取订阅者对象
    sub = rospy.Subscriber("hello", String, hell_callback, queue_size=10)

    # 3.回头
    rospy.spin()