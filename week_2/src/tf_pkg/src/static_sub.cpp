#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_sub");
    ros::NodeHandle nh;

    // 1.获取订阅对象tf2_ros::transform_listener
    // 1-1.创建缓存容器对象
    // tf2_ros/buffer.h（将订阅到的坐标系相对位置关系消息存在buffer中）
    tf2_ros::Buffer buffer;

    // 1-2.创建订阅对象，订阅话题中的所有消息存在buffer
    tf2_ros::TransformListener listener(buffer);

    // 2.组织一个坐标点（坐标系与点的位置关系）
    geometry_msgs::PointStamped ps;
    
    // 2-1.组织标头
    // 时间戳
    ps.header.stamp = ros::Time::now();
    // 参考坐标系
    ps.header.frame_id = "base_laser";

    // 2-2.组织位置关系
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;

    // 坐标点是相对于雷达的，是会不断更新的，所以需要在循环中转化相对底盘的位置
    ros::Rate rate(5);
    ros::Duration(2).sleep();
    while(ros::ok())
    {
        // 3.坐标点相对位置的转化
        // 需要tf2_geomtry_msgs/tf2_geometry_msgs.h
        // 将ps转换为相对于base_link的坐标
        geometry_msgs::PointStamped ps_out;
        ps_out = buffer.transform(ps,"base_link");

        // 显示转换后的坐标
        ROS_INFO("ps相对于base_link位置:(%.1f,%.1f,%.1f)",
                ps_out.point.x,ps_out.point.y,ps_out.point.z);

        rate.sleep();
        ros::spinOnce();

    }

    return 0;
}