#include <ros/ros.h>
#include <vector>

/*
    获取参数
    1.nh
        nh.param(参数名称，默认值)  
            如果查询的参数不存在，则返回默认值,存在则返回对应的值
        nh.getParam(参数名称，值)
            如果参数存在，返回true并将其赋值为指定的值，不存在则返回false
        nh.getParamCached(参数名称，值)
            用法和getparam一样，但是这个可以提高效率
            因为他是从缓存中读取数据，如果之前有读取该参数，可以直接从缓存读取
        nh.getParamNames(std::vector<std::string>)
            获取参数服务器中所有参数名称，并存在vector容器中
        nh.hasParam(参数名称)
            查询对应的参数是否存在，返回值类型是bool
        nh.searchParam(参数名称，储存参数)
            搜索参数，如果参数存在，则将参数名称赋值给储存参数
            不存在则为空
        

    2.ros::param
        ros::param::param(参数名，默认值)
        ros::param::get(参数名称，值)
        ros::param::getCached(参数名称，值)
        ros::param::getParamNames(vector<string>)
            获取全部的键存入vector<string>容器
        ros::param::has(参数名称)
        ros::param::search(参数名称，储存参数)

*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    // 1.初始化
    ros::init(argc,argv,"getparam");

    // 2.创建大管家
    ros::NodeHandle nh;

    // 3.查询并获取参数对应的值
    // nh.param(name,defualt)
    // ros::param::param(name,defualt);

    double radius = nh.param("radius",0);
    // double radius  = ros::param::param("radius",0);

    // 4.查询参数并对其赋值
    // nh.getparam(name,variable)
    // ros::param::get(name,variable)

    double radius2 = 0.5;
    bool result = nh.getParam("radius",radius2);
    // bool result = ros::param::get("radius",radius2);

    // 5.从缓存中查询参数并对其赋值
    // nh.getParamCached(name,variable)
    // ros::param::getCached(name,variable)

    // bool result = nh.getParamCached("radius",radius2);
    // bool rsult = ros::param::getCached("radius",radius2);

    if(result)
    {
        ROS_INFO("getparam查找参数radius成功，为其赋值为%.2f",radius2);
    }
    else
    {
        ROS_WARN("没有在参数服务器中找到radius参数");
    }

    // 6.获取全部参数名称
    // nh.getParamNames(vector<string>)
    // ros::getParamNames(vector<string>);
    std::vector<std::string> paramnames;
    nh.getParamNames(paramnames);
    // ros::getParamNames(paramnames)；

    // 遍历
    for(auto &&name : paramnames)
    {
        ROS_INFO("遍历元素：%s",name.c_str());
    }

    // 5.判断参数是否存在
    // nh.hasParam(name)
    // ros::param::has(name)

    bool hasparam = nh.hasParam("radius");
    if(hasparam)
    {
        ROS_INFO("存在参数radius");
    }
    else
    {
        ROS_WARN("参数radius不存在");
    }

    // 7.搜索参数
    // nh.searchParam()
    // ros::param::searche()
    
    std::string key;
    nh.searchParam("radiu",key);
    ROS_INFO("搜索结果：%s",key.c_str());

    return 0;
}
