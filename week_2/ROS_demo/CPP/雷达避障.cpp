#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

# �����ٶȿ��ƻ���(��Ϊȫ�ֱ��������������ڻص������е��ø÷�����ȡ��������)
ros::Publisher vel_pub;

# ÿ����ת��ʱ�䣨��������ã�ÿ����תʱ��ֻ��ÿ��ɨ��ļ��ʱ�䣬�����Ա��ϣ�
int ncount = 0;

# ÿɨ��һ�ܵ���һ�θûص�����
void LaserScanCallBack(sensor_msgs::LaserScan msg)
{
	# ��ȡǰ���ϰ��������Ϣ
		float fdist = msg.ranges[180];
	# �ٶȿ�����Ϣ��
		geometry_msgs::Twist vel_msgs;

	if (ncount > 0)
	{
		ncount--;
		return;
	}

	# ����
		if (fdist < 1.5)
		{
			# ������ת(����ÿ��)
				vel_msgs.angular.z = 0.5;
			# ��תʱ��5s
				time = 50;
		}
		else
		{
			vel_msgs.linear.x = 0.1;
		}

	# �����߽���Ϣ������������
		vel_pub.publish(vel_msg);
}

int main(int arcv, char* argc[])
{
	#��ʼ��
		ros::init(argc, argv, "ladir_behavior_node");
	# ���ļ����״��໰��
		ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("/scan", 10, LaserScanCallBack);
	# ���巢����
		vel_pub = = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

	ros::spin();

}
