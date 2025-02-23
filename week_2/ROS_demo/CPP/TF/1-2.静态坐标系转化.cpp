#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char* argv[])
{
    // 设置编码，正常显示中文
    setlocale(LC_ALL, "");

    // 初始化
    ros::init(argc, argv, "static_sub_node");
    ros::NodeHandle nh;

    // 创建订阅对象
    // 创建buffer对象缓存数据
    tf2_ros::Buffer buffer;
    // 创建监听对象(把订阅的数据缓存在buffer)
    tf2_ros::TransformListener listener(buffer);

    // 组织一个坐标点数据
    geometry_msgs::PointStamped ps;
    ps.header.frame_id = "laser";           // 参考坐标系
    ps.header.stamp = ros::Time::now();     // 时间戳
    // 在坐标系中的坐标
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;

    // 添加休眠（有可能我们已经开始转换工作了，但是实际上我们没有拿到发布者发布的数据，这样我们程序就会报错，所以要先休眠2秒之后再进行转换，确保已经拿到了数据）
    ros::Duration(2).sleep();

    // 在实际中，激光雷达是不断的扫描障碍物信息的，所以需要实时更新打印出相关信息
    ros::Rate rate(10);

    while (ros::ok())
    {
        // 核心算法：将相对于laser的坐标转换为相对于base_link的
        // 1.创建一个坐标点信息对象，用于接收转换操作后的坐标信息
        geometry_msgs::PointStamped ps_out;
        // 2.通过buffer内置转换函数实现转换
        ps_out = buffer.transform(ps, "base_link");

        // 3.输出信息
        ROS_INFO("转换后的坐标：（%.2f,%.2f,%.2f),参考坐标为：%s",
            ps_out.point.x,
            ps_out.point.y,
            ps_out.point.z,
            ps_out.header.frame_id.c_str());

        rate.sleep();
        ros::spinOnce();

    }

    return 0;
}
