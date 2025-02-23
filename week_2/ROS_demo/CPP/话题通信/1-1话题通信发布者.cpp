#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char* argv[])
{
    // 1.�����������
    setlocale(LC_ALL, "");

    // 2.�ڵ��ʼ��
    ros::init(argc, argv, "hello_pub_node");

    // 3.�����ڵ�ܼ�
    ros::NodeHandle nh;

    // 4.���������߶���
    ros::Publisher pub = nh.advertise<std_msgs::String>("hello", 10);

    // 5.������Ϣ����Ƶ�ʿ��ƶ���
    ros::Rate rate(10);

    // 6.��ȡ��Ϣ����
    int count = 0;
    std_msgs::String msg;

    while (ros::ok())
    {
        count++;
        ROS_INFO("�����߷�����%d����Ϣ", count);

        // 6.��֯��Ϣ
        msg.data = "hello";

        // 7.������Ϣ��������
        pub.publish(msg);

        // 8.Ƶ�ʿ���
        rate.sleep();

        // 9.spinOnce��ͷ����ѭ���еĻص�����������û�У�
        ros::spinOnce();
    }

    return 0;

}