#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char* argv[])
{
    // ���ñ��룬������ʾ����
    setlocale(LC_ALL, "");

    // ��ʼ��
    ros::init(argc, argv, "static_sub_node");
    ros::NodeHandle nh;

    // �������Ķ���
    // ����buffer���󻺴�����
    tf2_ros::Buffer buffer;
    // ������������(�Ѷ��ĵ����ݻ�����buffer)
    tf2_ros::TransformListener listener(buffer);

    // ��֯һ�����������
    geometry_msgs::PointStamped ps;
    ps.header.frame_id = "laser";           // �ο�����ϵ
    ps.header.stamp = ros::Time::now();     // ʱ���
    // ������ϵ�е�����
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;

    // ������ߣ��п��������Ѿ���ʼת�������ˣ�����ʵ��������û���õ������߷��������ݣ��������ǳ���ͻᱨ������Ҫ������2��֮���ٽ���ת����ȷ���Ѿ��õ������ݣ�
    ros::Duration(2).sleep();

    // ��ʵ���У������״��ǲ��ϵ�ɨ���ϰ�����Ϣ�ģ�������Ҫʵʱ���´�ӡ�������Ϣ
    ros::Rate rate(10);

    while (ros::ok())
    {
        // �����㷨���������laser������ת��Ϊ�����base_link��
        // 1.����һ���������Ϣ�������ڽ���ת���������������Ϣ
        geometry_msgs::PointStamped ps_out;
        // 2.ͨ��buffer����ת������ʵ��ת��
        ps_out = buffer.transform(ps, "base_link");

        // 3.�����Ϣ
        ROS_INFO("ת��������꣺��%.2f,%.2f,%.2f),�ο�����Ϊ��%s",
            ps_out.point.x,
            ps_out.point.y,
            ps_out.point.z,
            ps_out.header.frame_id.c_str());

        rate.sleep();
        ros::spinOnce();

    }

    return 0;
}
