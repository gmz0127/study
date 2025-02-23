#include <ros/ros.h>
#include "server_pkg/addint.h"
/*
    客户端：提交两个整数，并处理响应
        1.包含头文件
        2.setlocale，初始化
        3.创建大管家
        4.创建客户端对象
        5.提交请求并处理响应
*/
int main(int argc, char* argv[])
{
    // 2.setlocale，初始化
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "server_sub_node");

    // 3.创建大管家
    ros::NodeHandle nh;

    // 4.创建客户端对象
    ros::ServiceClient client = nh.serviceClient<server_pkg::addint>("/addint");

    // 5.提交请求并处理响应
    // 5-1.组织请求

    // 获取服务对象
    server_pkg::addint ai;
    // 获取服务请求对象
    ai.request.num1 = 1;
    ai.request.num2 = 2;

    // 5-2.处理响应

    // 客户端对象通过call函数查看是否成功处理请求
    bool flag = client.call(ai);

    // 针对是否成功处理来处理响应
    if (flag)
    {
        ROS_WARN("客户端接受响应");
        ROS_INFO("响应sums = %d", ai.response.sums);
    }
    else
    {
        ROS_WARN("客户端响应失败");
    }

    return 0;
}