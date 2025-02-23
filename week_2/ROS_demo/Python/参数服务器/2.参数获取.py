#!/usr/bin/env python3
# encoding=utf-8

import rospy

"""
    rospy.get_param(参数名称,默认值)
    rospy.get_param_cached(参数名称，赋值)
    rospy.get_param_name()
    rospy.has_param(参数名称)
    rospy.search_param()

"""

if __name__ == "__main__":
    rospy.init_node("getparam")

    # 1.获取参数对应的值，不存在则返回默认值
    radius = rospy.get_param("radius", 0)

    # 2.从缓存中获取参数对应的值，不存在则返回默认自
    radius2 = rospy.get_param_cached("radiuss", 0)

    # 3.获取参数服务器所有参数
    names = rospy.get_param_names()

    for name in names:
        rospy.loginfo("获取到的键：%s", name)

    # 4.判断某个参数是否存在
    flag = rospy.has_param("type")
    if flag:
        rospy.loginfo("参数存在")
    else:
        rospy.loginfo("参数不存在")

    # 5.查找参数，返回值是返回存在的参数，不存在则为空
    key = rospy.search_param("noexist_param")
    rospy.loginfo("找到的参数key=%s", key)
    # 找到的参数key=None
