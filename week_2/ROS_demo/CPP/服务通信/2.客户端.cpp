#include <ros/ros.h>
#include "server_pkg/addint.h"
/*
    �ͻ��ˣ��ύ������������������Ӧ
        1.����ͷ�ļ�
        2.setlocale����ʼ��
        3.������ܼ�
        4.�����ͻ��˶���
        5.�ύ���󲢴�����Ӧ
*/
int main(int argc, char* argv[])
{
    // 2.setlocale����ʼ��
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "server_sub_node");

    // 3.������ܼ�
    ros::NodeHandle nh;

    // 4.�����ͻ��˶���
    ros::ServiceClient client = nh.serviceClient<server_pkg::addint>("/addint");

    // 5.�ύ���󲢴�����Ӧ
    // 5-1.��֯����

    // ��ȡ�������
    server_pkg::addint ai;
    // ��ȡ�����������
    ai.request.num1 = 1;
    ai.request.num2 = 2;

    // 5-2.������Ӧ

    // �ͻ��˶���ͨ��call�����鿴�Ƿ�ɹ���������
    bool flag = client.call(ai);

    // ����Ƿ�ɹ�������������Ӧ
    if (flag)
    {
        ROS_WARN("�ͻ��˽�����Ӧ");
        ROS_INFO("��Ӧsums = %d", ai.response.sums);
    }
    else
    {
        ROS_WARN("�ͻ�����Ӧʧ��");
    }

    return 0;
}