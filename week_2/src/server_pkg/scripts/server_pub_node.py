#!/usr/bin/env python3
#encoding=utf-8

import rospy
from server_pkg.srv import *

"""
    服务端：解析客户端请求，产生响应
        1.导包
        2.初始化
        3.创建服务端对象
        4.处理请求，产生响应
            回调函数
        5.spin()

"""

def donums(request:addintRequest):
    """
        1.参数：封装了请求数据
        2.返回值：响应数据
    """
    # 处理请求
    num1 = request.num1
    num2 = request.num2

    # 处理响应
    sums = num1 + num2

    # 获取响应对象
    response = addintResponse()
    response.sums = sums

    rospy.loginfo("服务器解析数据num1=%d,num2=%d",num1,num2)
    rospy.loginfo("响应数据sums=%d",response.sums)

    # 返回响应数据
    return response


if __name__ =="__main__":
    

    # 1.初始化
    rospy.init_node("server_pub_node")

    # 2.获取服务端对象
    server = rospy.Service("/addint",addint,donums)

    # 3.回头
    rospy.spin()