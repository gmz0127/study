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
int main(int argc, char *argv[])
{
    // argc:代表传入参数的总数量
    // 本案例共三个参数：程序名称，num1,num2
    if(argc != 3)
    {
        ROS_WARN("传入参数个数不对！");
        return 0;
    }

    setlocale(LC_ALL,"");
    ros::init(argc,argv,"server_sub_node");
    ros::NodeHandle nh;

    // 4.创建客户端对象
    ros::ServiceClient client = nh.serviceClient<server_pkg::addint>("/addint");

    // 5.提交请求并处理响应
    // 5-1.组织请求

    // 获取服务对象
    server_pkg::addint ai;
    // 获取服务请求对象
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);

    // 5-2.处理响应

    // 等待服务端启动
    client.waitForExistence();

    // 客户端对象通过call函数查看是否成功处理请求
    bool flag = client.call(ai);

    if(flag)
    {
        ROS_WARN("客户端接受响应");
        ROS_INFO("响应sums = %d",ai.response.sums);
    }
    else
    {
        ROS_WARN("客户端响应失败");
    }
    return 0;
}
