#include <ros/ros.h>
#include "server_pkg/addint.h"

/*
服务端实现：
    1.包含头文件
    2.初始化
    3.获取大管家
    4.创建服务对象
    5.处理请求并响应
    6.spin()
*/

// 服务端的回调函数
// 参数：请求对象，响应对象
bool donums(server_pkg::addint::Request& rq,
            server_pkg::addint::Response& rp)
{
    // 1.处理请求
    int num1 = rq.num1;
    int num2 = rq.num2;
    ROS_INFO("收到的请求数据num1：%d,num2:%d",num1,num2);

    // 2.组织相应
    int sum = num1 + num2;
    rp.sums = sum;
    ROS_INFO("处理后的数据sum:%d",sum);

    return true;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"complish_server_node");
    ros::NodeHandle nh;
    
    // 创建服务对象
    // 使用adevtiseServer(话题，回调函数)；
    // 返回值是布尔类型，看是否处理成功
    ros::ServiceServer server = nh.advertiseService("/addint",donums);

    ROS_INFO("服务端启动");

    ros::spin();
    return 0;
}