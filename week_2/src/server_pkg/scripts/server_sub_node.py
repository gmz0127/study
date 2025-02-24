#!/usr/bin/env python3
#encoding=utf-8

import rospy
from server_pkg.srv import*
import sys

if __name__ == "__main__":
    # 优化实现，参数的动态提交
    # 需要包含库文件sys

    # 判断传入的参数个数
    if len(sys.argv) != 3:
        rospy.loginfo("传入参数个数不对！")
        sys.exit(1)


    # 初始化
    rospy.init_node("server_sub_node")
    
    # 获取客户端对象
    client = rospy.ServiceProxy("/addint",addint)

    # 组织请求，获取响应
    num1 = int(sys.argv[1])
    num2 = int(sys.argv[2])

    # 优化实现
    # 2.客户端挂起
    # 2-1通过客户端对象挂起
    client.wait_for_service()

    # 2-2 通过rospy挂起
    # 传入的参数是要等待的服务话题
    rospy.wait_for_service("/addint")
    
    response = client.call(num1,num2)

    # 处理请求
    rospy.loginfo("响应的数据sums=%d",response.sums)
    