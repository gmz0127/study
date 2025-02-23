#include <ros/ros.h>
#include <std_msgs/String.h>

// ���ص�����һ����const����
void hello_callback(const std_msgs::String& msg)
{
    // ��ӡ���յ�����Ϣ
    ROS_INFO("���յ�����Ϣ��:%s", msg.data.c_str());

}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "hello_sub_node");

    // 1.������ܼ�
    ros::NodeHandle nh;

    // 2.���������Ŷ���
    ros::Subscriber sub = nh.subscribe("hello", 10, hello_callback);

    // 3.��ͷ�鿴��Ϣ����ص�����
    ros::spin();

    return 0;
}