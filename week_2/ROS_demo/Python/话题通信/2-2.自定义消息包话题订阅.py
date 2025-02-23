#!/usr/bin/env python3
# encoding=utf-8

import rospy
from mymsgs.msg import person


def mymsg_callback(p):
    rospy.loginfo("%s,%d,%.2f", p.name, p.age, p.height)


if __name__ == "__main__":
    rospy.init_node("mymsg_sub_node")

    sub = rospy.Subscriber("mymsg", person, mymsg_callback, queue_size=10)

    rospy.spin()