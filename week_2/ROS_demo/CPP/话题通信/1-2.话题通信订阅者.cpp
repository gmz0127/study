#include <ros/ros.h>
#include <std_msgs/String.h>

// ！回调函数一定是const类型
void hello_callback(const std_msgs::String& msg)
{
    // 打印接收到的消息
    ROS_INFO("接收到的消息是:%s", msg.data.c_str());

}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "hello_sub_node");

    // 1.创建大管家
    ros::NodeHandle nh;

    // 2.创建订阅着对象
    ros::Subscriber sub = nh.subscribe("hello", 10, hello_callback);

    // 3.回头查看消息处理回调函数
    ros::spin();

    return 0;
}