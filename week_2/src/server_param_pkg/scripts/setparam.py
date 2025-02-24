#!/usr/bin/env python3
#encoding=utf-8

import rospy

if __name__ =="__main__":
    rospy.init_node("setparam")

    # 参数的新增
    # rospy.set_param(参数名称，参数值)
    rospy.set_param("type","yellowCar")
    rospy.set_param("radius",0.5)

    # 参数的修改
    rospy.set_param("radius",0.1)