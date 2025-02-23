#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>

/*
    ����������Ҫ�����ڹ��λ����Ϣ��ת��������ϵ�����λ�ù�ϵ������
    ׼  ����
        ���⣺/turtle1/pose
        ��Ϣ��/turtlesim/Pose

    ���̣�
        1.����ͷ�ļ�
        2.���ñ��룬�ڵ��ʼ��
        3.�������Ķ��󣬶���/turtle1/pose����
        4.�ص�������������Ҫ�ڻص������л�ȡ��Ϣ��ת��tf����
        5.spin()��ͷ

*/

void delPose(const turtlesim::Pose& pose)
{
    // 1.����tf��������
    // ��̬��ϵʹ��tf2_ros/transform_broadcaster.h
    // ����Ϊ��̬�������Ͳ���Ҫÿ�ζ��������󣬶���ʹ�þ�̬����
    static tf2_ros::TransformBroadcaster pub;

    // 2.ת��������ϵ���ϵ
    // 2-2.��ȡtf����ϵ��λ�ù�ϵ��Ϣ����
    geometry_msgs::TransformStamped tfs;

    // ʱ���
    tfs.header.stamp = ros::Time::now();
    // ��ϵ����ϵ
    tfs.header.frame_id = "world";

    // �ڹ������ϵ
    tfs.child_frame_id = "turtlesim";

    // ���λ��
    tfs.transform.translation.x = pose.x;
    tfs.transform.translation.y = pose.y;
    tfs.transform.translation.z = 0;

    // ŷ����תΪ��Ԫ��
    // �ڹ���2D�ģ�ֻ��z��ƫ���ǣ�����ͨ���ڹ�λ�˵ĳ���theta��ȡ
    tf2::Quaternion qnt;
    qnt.setRPY(0, 0, pose.theta);
    tfs.transform.rotation.x = qnt.getX();
    tfs.transform.rotation.y = qnt.getY();
    tfs.transform.rotation.z = qnt.getZ();
    tfs.transform.rotation.w = qnt.getW();

    // ��������
    pub.sendTransform(tfs);

}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "domatic_pub");
    ros::NodeHandle nh;

    // �������Ķ��󣨶����ڹ�λ�˻��⣩
    ros::Subscriber sub = nh.subscribe("/turtle1/pose", 100, delPose);

    // spin()
    ros::spin();

    return 0;
}