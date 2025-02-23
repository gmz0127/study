#include <ros/ros.h>

/*
    ������ɾ��
        1.nh
            deleteParam(name)
            ����ֵbool���ͣ����Ƿ�ɾ���ɹ�
        2.ros::param
            del()

*/
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "delparam");
    ros::NodeHandle nh;

    // 1.nh.deleteParam(name)
    bool flag = nh.deleteParam("radius_param");

    // 2.ros::param::del(name)
    bool flag2 = ros::param::del("radius");

    if (flag)
    {
        ROS_INFO("ɾ�������ɹ�");
    }
    else
    {
        ROS_INFO("ɾ������ʧ��");
    }

    return 0;
}