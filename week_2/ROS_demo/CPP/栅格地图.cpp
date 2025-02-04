#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>

int main(int argc, char* argv[])
{

    ros::init(argc, argv, "map_pub_node");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<nav_msgs::OccupancyGrid>("/map", 10);

    ros::Rate rate(1);

    // ��ȡ��ͼ��Ϣ��
    nav_msgs::OccupancyGrid msg;
    // ��ֵ
    msg.header.frame_id = "map";
    // ʱ�������Ϊ��ǰʱ��
    msg.header.stamp = ros::Time::now();

    msg.info.origin.position.x = 0;
    msg.info.origin.position.y = 0;
    // ��ͼ�ֱ��ʣ���ÿդ��
    msg.info.resolution = 1.0;
    // ��ͼ��С
    msg.info.width = 4;
    msg.info.height = 2;

    //���������С���*�߶�
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
