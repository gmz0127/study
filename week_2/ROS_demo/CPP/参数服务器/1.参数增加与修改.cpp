#include <ros/ros.h>

/*
    ʵ�ֲ��������������
    ���������û����˵Ĺ�����������ͣ��뾶��Ȼ���޸�
    ʵ�֣�
        1.ros::NodeHandle
            setParam()
        2.ros::param
            set()
*/

int main(int argc, char* argv[])
{
    // 1.��ʼ��
    ros::init(argc, argv, "setparam_node");

    // 2.����ros��ܼ�
    ros::NodeHandle nh;

    // 3.��������
    // 3-1.ros::NodeHandle
    // nh.setParam(������������ֵ)
    nh.setParam("type", "smartrobot");
    nh.setParam("radius", 0.15);

    // 3-2.ros::param
    // ros::param::set("type","smartrobot");
    // ros::param::set("radius",0.15);

    return 0;
}
