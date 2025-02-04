#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>

int main(int argc, char* argv[])
{

    ros::init(argc, argv, "map_pub_node");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<nav_msgs::OccupancyGrid>("/map", 10);

    ros::Rate rate(1);

    // 获取地图消息包
    nav_msgs::OccupancyGrid msg;
    // 赋值
    msg.header.frame_id = "map";
    // 时间戳设置为当前时间
    msg.header.stamp = ros::Time::now();

    msg.info.origin.position.x = 0;
    msg.info.origin.position.y = 0;
    // 地图分辨率（米每栅格）
    msg.info.resolution = 1.0;
    // 地图大小
    msg.info.width = 4;
    msg.info.height = 2;

    //调整数组大小宽度*高度
    msg.data.resize(4 * 2);
    msg.data[0] = 100;
    msg.data[1] = 100;
    msg.data[2] = 0;
    msg.data[3] = -1;

    while (ros::ok())
    {
        pub.publish(msg);
        rate.sleep();

    }

    return 0;
}
