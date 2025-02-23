#!/usr/bin/env python3
# encoding=utf-8

import rospy
from server_pkg.srv import *

if __name__ == "__main__":
    # 初始化
    rospy.init_node("server_sub_node")

    # 获取客户端对象
    client = rospy.ServiceProxy("/addint", addint)

    # 组织请求，获取响应
    response = client.call(12, 34)

    # 处理请求
    rospy.loginfo("响应的数据sums=%d", response.sums)