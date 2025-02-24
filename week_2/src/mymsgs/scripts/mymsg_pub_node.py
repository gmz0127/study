#!/usr/bin/env python3
#encoding=utf-8

import rospy
from mymsgs.msg import person

if __name__ == "__main__":
    rospy.init_node("mymsg_pub_node")

    pub = rospy.Publisher("mymsg",person,queue_size=10)

    rate = rospy.Rate(5)
    rospy.sleep(2)

    count = 0
    p = person()
    p.name = "gmz"
    p.age=18
    p.height = 200

    while not rospy.is_shutdown():
        p.age+=1
        pub.publish(p)
        count+=1
        rospy.loginfo("发布第%d条数据",count)
        rate.sleep()