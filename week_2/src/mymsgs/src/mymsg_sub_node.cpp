#include <ros/ros.h>
#include <mymsgs/person.h>

void msg_callback(const mymsgs::person p)
{
    ROS_INFO("接收到的消息：%s,%d,%.2f",p.name.c_str(),p.age,p.height);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"mymsg_sub_node");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("mymsg",10,msg_callback);

    ros::spin();

    return 0;
}