#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

ros::Publisher vel_pub;
int time_ang = 0;

void LaserScanCallBack(sensor_msgs::LaserScan msg)
{
    float fdist = msg.ranges[180];
    ROS_INFO("distant:%f",fdist);
    geometry_msgs::Twist vel_msg;

    if(time_ang > 0)
    {
        time_ang--;
        return;
    }

    if(fdist < 1.5)
    {
        vel_msg.angular.z = 0.3;
        time_ang = 50;
    }
    else{
        vel_msg.linear.x = 0.1;
    }
    vel_pub.publish(vel_msg);

}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"ladir_behavior_node");

    ros::NodeHandle nh;
    ros::Subscriber ladir_sub = nh.subscribe("/scan",10,LaserScanCallBack);
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);

    ros::spin();

    return 0;
}
