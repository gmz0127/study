#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>

/*
    发布方：需要订阅乌龟的位姿信息，转换成坐标系的相对位置关系并发布
    准  备：
        话题：/turtle1/pose
        消息：/turtlesim/Pose

    流程：
        1.包含头文件
        2.设置编码，节点初始化
        3.创建订阅对象，订阅/turtle1/pose话题
        4.回调函数构建，需要在回调函数中获取信息并转换tf发布
        5.spin()回头

*/

void delPose(const turtlesim::Pose& pose)
{
    // 1.创建tf发布对象
    // 动态关系使用tf2_ros/transform_broadcaster.h
    // 声明为静态变量，就不需要每次都创建对象，而是使用静态变量
    static tf2_ros::TransformBroadcaster pub;

    // 2.转化成坐标系间关系
    // 2-2.获取tf坐标系间位置关系消息对象
    geometry_msgs::TransformStamped tfs;

    // 时间戳
    tfs.header.stamp = ros::Time::now();
    // 父系坐标系
    tfs.header.frame_id = "world";

    // 乌龟的坐标系
    tfs.child_frame_id = "turtlesim";

    // 相对位置
    tfs.transform.translation.x = pose.x;
    tfs.transform.translation.y = pose.y;
    tfs.transform.translation.z = 0;

    // 欧拉角转为四元素
    // 乌龟是2D的，只有z的偏航角，可以通过乌龟位姿的朝向theta获取
    tf2::Quaternion qnt;
    qnt.setRPY(0, 0, pose.theta);
    tfs.transform.rotation.x = qnt.getX();
    tfs.transform.rotation.y = qnt.getY();
    tfs.transform.rotation.z = qnt.getZ();
    tfs.transform.rotation.w = qnt.getW();

    // 发布对象
    pub.sendTransform(tfs);

}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "domatic_pub");
    ros::NodeHandle nh;

    // 创建订阅对象（订阅乌龟位姿话题）
    ros::Subscriber sub = nh.subscribe("/turtle1/pose", 100, delPose);

    // spin()
    ros::spin();

    return 0;
}