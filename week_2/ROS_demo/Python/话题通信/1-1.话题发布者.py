#!/usr/bin/env python3
# encoding=utf-8

import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    # 1.初始化
    rospy.init_node("hello_pub_node")

    # 2.创建发布者对象
    pub = rospy.Publisher("hello", String, queue_size=10)

    # 3.创建频率控制对象
    rate = rospy.Rate(10)

    # 4.获取消息对象
    count = 0
    msg = String()

    # 5.休眠等待发布者注册成功
    rospy.sleep(3)

    while not rospy.is_shutdown():
        count += 1

        # 6.组织消息
        msg.data = "hello" + str(count)

        # 7.发布消息
        pub.publish(msg)

        # 8.控制频率
        rate.sleep()

        # 9.打印相关信息
        rospy.loginfo("发布的消息：%s", msg.data)