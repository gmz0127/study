#!/usr/bin/env python3
#encoding=utf-8

import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    # 1.初始化
    rospy.init_node("hello_pub_node")
    
    # 2.获取发布者
    pub = rospy.Publisher("hello",String,queue_size=10)

    # 3.获取信息频率控制对象
    rate = rospy.Rate(10)

    # 4.获取消息对象
    count = 0
    msg = String()

    while rospy.is_shutdown():
        # 5.组织消息
        msg.data = "hello" + count

        # 6.发布消息
        pub.publish(msg)

        # 7.·频率控制
        rate.sleep()

        

