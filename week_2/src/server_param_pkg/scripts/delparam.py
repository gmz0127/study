#!/usr/bin/env python3
#encoding=utf-8

import rospy
"""
    rospy.delte_param(参数名称)
    参数存在删除成功，参数不存在则会抛出异常

"""

if __name__ =="__main__":
    rospy.init_node("delparam")

    # 删除参数
    try:
        rospy.delete_param("hhh")
    except Exception as e:
        rospy.loginfo("被删除的参数不存在")