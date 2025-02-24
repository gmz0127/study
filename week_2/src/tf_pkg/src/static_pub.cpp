#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_pub");
    ros::NodeHandle nh;

    // 1.创建发布对象（使用tf封装好的，依赖性：tf2_ros）
    // 因为是静态坐标，所以使用tf2_ros/static_transform_broadcaster
    tf2_ros::StaticTransformBroadcaster pub;


    // 2.组织发布消息
    // 坐标系相对位置关系：geometry_msgs/TransformStamped
    geometry_msgs::TransformStamped tfs;

    // 2-1.设置标头Header
    // 时间戳
    tfs.header.stamp = ros::Time::now();
    // 参考坐标系
    tfs.header.frame_id = "base_link";

    // 2-2.设置子坐标系
    tfs.child_frame_id = "base_laser";

    // 2-3.设置两坐标系x,y,z相对位置关系
    tfs.transform.translation.x = 0.2;
    tfs.transform.translation.y = 0.0;
    tfs.transform.translation.z = 0.5;

    // 2-3.设置两坐标系四元数（欧拉角关系）
    // tf2内置了欧拉角转化四元数的方法(tf2/LinearMath/Quaternion)
    // 获取四元素对象
    tf2::Quaternion qtn;
    // 向四元素对象传入对应的欧拉角(单位是弧度)
    qtn.setRPY(0,0,0);
    // 获取转换后的四元素
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();


    // 3.发布消息（因为是静态消息，只需要发布一次就可以了）
    pub.sendTransform(tfs);
    
    ros::spin();

    return 0;
}
