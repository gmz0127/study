#include <ros/ros.h>
#include <vector>

/*
    ��ȡ����
    1.nh
        nh.param(�������ƣ�Ĭ��ֵ)
            �����ѯ�Ĳ��������ڣ��򷵻�Ĭ��ֵ,�����򷵻ض�Ӧ��ֵ
        nh.getParam(�������ƣ�ֵ)
            ����������ڣ�����true�����丳ֵΪָ����ֵ���������򷵻�false
        nh.getParamCached(�������ƣ�ֵ)
            �÷���getparamһ������������������Ч��
            ��Ϊ���Ǵӻ����ж�ȡ���ݣ����֮ǰ�ж�ȡ�ò���������ֱ�Ӵӻ����ȡ
        nh.getParamNames(std::vector<std::string>)
            ��ȡ���������������в������ƣ�������vector������
        nh.hasParam(��������)
            ��ѯ��Ӧ�Ĳ����Ƿ���ڣ�����ֵ������bool
        nh.searchParam(�������ƣ��������)
            ��������������������ڣ��򽫲������Ƹ�ֵ���������
            ��������Ϊ��


    2.ros::param
        ros::param::param(��������Ĭ��ֵ)
        ros::param::get(�������ƣ�ֵ)
        ros::param::getCached(�������ƣ�ֵ)
        ros::param::getParamNames(vector<string>)
            ��ȡȫ���ļ�����vector<string>����
        ros::param::has(��������)
        ros::param::search(�������ƣ��������)

*/
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    // 1.��ʼ��
    ros::init(argc, argv, "getparam");

    // 2.������ܼ�
    ros::NodeHandle nh;

    // 3.��ѯ����ȡ������Ӧ��ֵ
    // nh.param(name,defualt)
    // ros::param::param(name,defualt);

    double radius = nh.param("radius", 0);
    // double radius  = ros::param::param("radius",0);

    // 4.��ѯ���������丳ֵ
    // nh.getparam(name,variable)
    // ros::param::get(name,variable)

    double radius2 = 0.5;
    bool result = nh.getParam("radius", radius2);
    // bool result = ros::param::get("radius",radius2);

    // 5.�ӻ����в�ѯ���������丳ֵ
    // nh.getParamCached(name,variable)
    // ros::param::getCached(name,variable)

    // bool result = nh.getParamCached("radius",radius2);
    // bool rsult = ros::param::getCached("radius",radius2);

    if (result)
    {
        ROS_INFO("getparam���Ҳ���radius�ɹ���Ϊ�丳ֵΪ%.2f", radius2);
    }
    else
    {
        ROS_WARN("û���ڲ������������ҵ�radius����");
    }

    // 6.��ȡȫ����������
    // nh.getParamNames(vector<string>)
    // ros::getParamNames(vector<string>);
    std::vector<std::string> paramnames;
    nh.getParamNames(paramnames);
    // ros::getParamNames(paramnames)��

    // ����
    for (auto&& name : paramnames)
    {
        ROS_INFO("����Ԫ�أ�%s", name.c_str());
    }

    // 5.�жϲ����Ƿ����
    // nh.hasParam(name)
    // ros::param::has(name)

    bool hasparam = nh.hasParam("radius");
    if (hasparam)
    {
        ROS_INFO("���ڲ���radius");
    }
    else
    {
        ROS_WARN("����radius������");
    }

    // 7.��������
    // nh.searchParam()
    // ros::param::searche()

    std::string key;
    nh.searchParam("radiu", key);
    ROS_INFO("���������%s", key.c_str());

    return 0;
}