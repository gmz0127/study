#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

void SensorCallback(sensor_msgs::LaserScan msg)
{
    float fMidDist = msg.ranges[180];
    ROS_INFO("distant:%f",fMidDist);

}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"sensor_node");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/scan",10,SensorCallback);

    ros::spin();
    
    return 0;
}
