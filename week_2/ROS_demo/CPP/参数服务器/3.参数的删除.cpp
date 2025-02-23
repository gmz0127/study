#include <ros/ros.h>

/*
    参数的删除
        1.nh
            deleteParam(name)
            返回值bool类型，看是否删除成功
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
        ROS_INFO("删除参数成功");
    }
    else
    {
        ROS_INFO("删除参数失败");
    }

    return 0;
}