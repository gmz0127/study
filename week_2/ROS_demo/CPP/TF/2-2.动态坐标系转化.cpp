#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "domatic_sub");

    // 1.������̬���궩�Ķ���
    // ����������
    tf2_ros::Buffer buffer;

    // ������������
    tf2_ros::TransformListener listener(buffer);

    // 2.�����������Ϣ��������ڹ������㣩
    geometry_msgs::PointStamped ps;
    ps.header.stamp = ros::Time(0.0);
    ps.header.frame_id = "turtlesim";
    ps.point.x = 2.0;
    ps.point.y = 2.0;
    ps.point.z = 2.0;

    // �������
    ros::Duration(2).sleep();

    // ����任����Ƶ��
    ros::Rate rate(1);

    while (ros::ok())
    {
        // 3.����仯
        geometry_msgs::PointStamped ps_out;
        ps_out = buffer.transform(ps, "world");

        // 4.����任���չʾ
        ROS_INFO("�õ������%s������(%.2f,%.2f,%.2f)",
            ps.header.frame_id.c_str(),
            ps.point.x, ps.point.y, ps.point.y);

        ROS_INFO("�õ������%s������(%.2f,%.2f,%.2f)",
            ps_out.header.frame_id.c_str(),
            ps_out.point.x, ps_out.point.y, ps_out.point.y);

        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}