#include <ros/ros.h>
#include <mymsgs/person.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "mymsg_pub");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<mymsgs::person>("mymsg", 10);

    ros::Rate rate(5);
    ros::Duration(2).sleep();

    int count = 0;
    mymsgs::person p;
    p.name = "甘明珍";
    p.age = 20;
    p.height = 200.5;

    while (ros::ok())
    {
        pub.publish(p);

        count++;
        ROS_INFO("发送第%d条数据", count);

        rate.sleep();
    }

    return 0;
}