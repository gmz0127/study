#include <ros/ros.h>

/*
    实现参数的新增与更改
    需求：先设置机器人的共享参数，类型，半径，然后修改
    实现：
        1.ros::NodeHandle
            setParam()
        2.ros::param
            set()
*/


int main(int argc, char *argv[])
{
    // 1.初始化
    ros::init(argc,argv,"setparam_node");

    // 2.创建ros大管家
    ros::NodeHandle nh;

    // 3.新增参数
    // 3-1.ros::NodeHandle
    // nh.setParam(参数名，参数值)
    nh.setParam("type","smartrobot");
    nh.setParam("radius",0.15);

    // 3-2.ros::param
    ros::param::set("type_param","newsmartrobot");
    ros::param::set("radius_param",0.25);
    

    // 4.参数的修改
    // 4-1.nh.setParam覆盖重写参数
    nh.setParam("radius",0.5);

    // 4-2.ros::param::set()覆盖重写
    ros::param::set("radius_param",0.6);

    
    return 0;
}
