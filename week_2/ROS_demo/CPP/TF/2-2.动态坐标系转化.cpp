#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "domatic_sub");

    // 1.创建动态坐标订阅对象
    // 创建缓存器
    tf2_ros::Buffer buffer;

    // 创建监听对象
    tf2_ros::TransformListener listener(buffer);

    // 2.创建坐标点信息（相对于乌龟的坐标点）
    geometry_msgs::PointStamped ps;
    ps.header.stamp = ros::Time(0.0);
    ps.header.frame_id = "turtlesim";
    ps.point.x = 2.0;
    ps.point.y = 2.0;
    ps.point.z = 2.0;

    // 添加休眠
    ros::Duration(2).sleep();

    // 坐标变换更新频率
    ros::Rate rate(1);

    while (ros::ok())
    {
        // 3.坐标变化
        geometry_msgs::PointStamped ps_out;
        ps_out = buffer.transform(ps, "world");

        // 4.坐标变换后的展示
        ROS_INFO("该点相对于%s的坐标(%.2f,%.2f,%.2f)",
            ps.header.frame_id.c_str(),
            ps.point.x, ps.point.y, ps.point.y);

        ROS_INFO("该点相对于%s的坐标(%.2f,%.2f,%.2f)",
            ps_out.header.frame_id.c_str(),
            ps_out.point.x, ps_out.point.y, ps_out.point.y);

        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}