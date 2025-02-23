#include <ros/ros.h>
#include "server_pkg/addint.h"

/*
�����ʵ�֣�
    1.����ͷ�ļ�
    2.��ʼ��
    3.��ȡ��ܼ�
    4.�����������
    5.����������Ӧ
    6.spin()
*/

// ����˵Ļص�����
// ���������������Ӧ����
bool donums(server_pkg::addint::Request& rq,
    server_pkg::addint::Response& rp)
{
    // 1.��������
    int num1 = rq.num1;
    int num2 = rq.num2;
    ROS_INFO("�յ����������ݣ�num1��%d,num2:%d", num1, num2);

    // 2.��֯��Ӧ
    int sum = num1 + num2;
    rp.sums = sum;
    ROS_INFO("����������sum:%d", sum);

    return true;
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "complish_server_node");
    ros::NodeHandle nh;

    // �����������
    // ʹ��adevtiseServer(���⣬�ص�����)��
    // ����ֵ�ǲ������ͣ����Ƿ���ɹ����ص��������ڴ�������
    ros::ServiceServer server = nh.advertiseService("/addint", donums);

    // ��ͷ��һֱ�鿴�Ƿ������󣬴���ص�����
    ros::spin();
    return 0;
}