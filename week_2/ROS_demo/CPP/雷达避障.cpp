#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

# 发布速度控制话题(作为全局变量，这样可以在回调函数中调用该发布者取发布话题)
ros::Publisher vel_pub;

# 每次旋转的时间（如果不设置，每次旋转时间只有每次扫描的间隔时间，不足以避障）
int ncount = 0;

# 每扫描一周调用一次该回调函数
void LaserScanCallBack(sensor_msgs::LaserScan msg)
{
	# 获取前方障碍物距离信息
		float fdist = msg.ranges[180];
	# 速度控制信息包
		geometry_msgs::Twist vel_msgs;

	if (ncount > 0)
	{
		ncount--;
		return;
	}

	# 避障
		if (fdist < 1.5)
		{
			# 向左旋转(弧度每秒)
				vel_msgs.angular.z = 0.5;
			# 旋转时间5s
				time = 50;
		}
		else
		{
			vel_msgs.linear.x = 0.1;
		}

	# 发布者将消息发布到话题上
		vel_pub.publish(vel_msg);
}

int main(int arcv, char* argc[])
{
	#初始化
		ros::init(argc, argv, "ladir_behavior_node");
	# 订阅激光雷达测距话题
		ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("/scan", 10, LaserScanCallBack);
	# 定义发布者
		vel_pub = = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

	ros::spin();

}
