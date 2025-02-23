#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char* argv[])
{
    // 1.解决乱码问题
    setlocale(LC_ALL, "");

    // 2.节点初始化
    ros::init(argc, argv, "hello_pub_node");

    // 3.创建节点管家
    ros::NodeHandle nh;

    // 4.创建发布者对象
    ros::Publisher pub = nh.advertise<std_msgs::String>("hello", 10);

    // 5.创建消息发布频率控制对象
    ros::Rate rate(10);

    // 6.获取消息对象
    int count = 0;
    std_msgs::String msg;

    while (ros::ok())
    {
        count++;
        ROS_INFO("发布者发布第%d条消息", count);

        // 6.组织消息
        msg.data = "hello";

        // 7.发布消息到话题中
        pub.publish(msg);

        // 8.频率控制
        rate.sleep();

        // 9.spinOnce回头处理循环中的回调函数（这里没有）
        ros::spinOnce();
    }

    return 0;

}