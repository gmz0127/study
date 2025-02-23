#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

/*
������ͷ�ļ�
1.ros/ros.h
2.geometry_msgs/TransfrmStamped.h
    �������������λ�ù�ϵ����Ϣ��

3.tf2_ros/static_transform_boardcaster.h
    tf��̬���귢���Ĺ㲥ϵͳ�����ڴ���������̬����ϵ��Ϣ�ķ�����
    ע��tf�Լ��ѷ����ߣ���������Ĳ����װ�����ˣ�ֻ��Ҫ����tf�ķ����߾Ϳ���ʵ��nodehandle��ܼҴ���������ͬʱ��������/tf_static�������÷�����Ϣ��Ҳ�����֯�õ���Ϣ����������

4.<tf2/LinearMath/Quaternion.h>
    ����ʹ��ŷ����ת��Ϊ��Ԫ��
*/

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "static_pub");

    // 1.������������ʹ��tf��װ�õģ������ԣ�tf2_ros��
    // ��Ϊ�Ǿ�̬���꣬����ʹ��tf2_ros/static_transform_broadcaster
    tf2_ros::StaticTransformBroadcaster pub;


    // 2.��֯������Ϣ
    // ����ϵ���λ�ù�ϵ��geometry_msgs/TransformStamped
    geometry_msgs::TransformStamped tfs;

    // 2-1.���ñ�ͷHeader
    // ʱ���
    tfs.header.stamp = ros::Time::now();
    // �ο�����ϵ
    tfs.header.frame_id = "base_link";

    // 2-2.����������ϵ
    tfs.child_frame_id = "base_laser";

    // 2-3.����������ϵx,y,z���λ�ù�ϵ
    tfs.transform.translation.x = 0.2;
    tfs.transform.translation.y = 0.0;
    tfs.transform.translation.z = 0.5;

    // 2-3.����������ϵ��Ԫ����ŷ���ǹ�ϵ��
    // tf2������ŷ����ת����Ԫ���ķ���(tf2/LinearMath/Quaternion)
    // ��ȡ��Ԫ�ض���
    tf2::Quaternion qtn;
    // ����Ԫ�ض������Ӧ��ŷ����(��λ�ǻ���)
    qtn.setRPY(0, 0, 0);
    // ��ȡת�������Ԫ��
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();


    // 3.������Ϣ����Ϊ�Ǿ�̬��Ϣ��ֻ��Ҫ����һ�ξͿ����ˣ�
    pub.sendTransform(tfs);

    // ����ѭ��
    ros::spin();

    return 0;
}