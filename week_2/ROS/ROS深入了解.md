# ROS架构

## ROS文件系统

![](C:\Users\HP\Desktop\ROS\img\ROS文件系统.png)

* **devel：开发空间**，用于存放编译后1生成的目标文件，包括头文件，可执行文件，动态静态连接库等
* **build：编译空间**，用于存放CMake和catkin的缓存信息，配置信息和中间文件
* **src：源码**，用于存放各种功能包
  * **package：功能包**，包含多个节点，库和配置文件
    * CMakeList.txt：配置编译规则，比如源文件，依赖项，目标文件
    * package.xml：包信息，比如包名，版本，作者，依赖项....
    * src：存放C++源文件
    * scripts：存放.py等脚本文件
    * msg：消息通信格式文件
    * srv：服务消息通信格式文件
    * launch：存放.launch文件
    * action：动作格式文件
    * config：配置信息

**package.xml文件**
包信息，比如包名，版本，作者，依赖项....

但最重要的信息以及需要自己设置的部分：（51行开始这部分，前面主要是版本，包名，作者等信息）

```
 # 当前功能包编译的时候依赖的编译工具
  <buildtool_depend>catkin</buildtool_depend>
 
 # 编译的时候依赖的功能包
  <build_depend>roscpp</build_depend>
  <build_depend>rospy</build_depend>
  <build_depend>std_msgs</build_depend>
 
 # 导出依赖
  <build_export_depend>roscpp</build_export_depend>
  <build_export_depend>rospy</build_export_depend>
  <build_export_depend>std_msgs</build_export_depend>
  
 # 执行依赖
  <exec_depend>roscpp</exec_depend>
  <exec_depend>rospy</exec_depend>
  <exec_depend>std_msgs</exec_depend>

```



## ROS文件系统相关命令

**1.增**

* catkin_create_pkg 自定义包名 依赖项    == 创建一个新的ROS功能包
* sudo apt install xxx == 安装ROS功能包

**2.删**

* sudo apt purge xxx == 删除某个功能包

**3.查**

* rospack list == 列出所有功能包

* rospack find 包名==查询某个功能包是否存在，存在则返回途径

* roscd 包名==进去某个功能包

* rosls 包名==列出该功能包下所有的文件

  

**4.改**

* rosed 包名 文件名 == 修改文件内容



**5.执行**

* roscore == ROS系统先决条件节点和程序的集合，必须运行roscore，ROS的内核才能使ROS节点进行通信
  roscore启动，将会启动ros master，ros 参数服务器,rosout日志节点
* rosrun 包名 可执行文件名称 == 运行某个包下指定的节点
* roslaunch 包名 launch文件 == 运行某个包下的launch文件



## ROS计算图

ros程序运行之后，不同的节点之间使错综复杂的，ROS提供了一个工具rqt_graph。rqt_graph能够创建一个显示当前系统运行情况的动态图形。

**计算图安装**

```
# <distro>用你安装的ros版本代替，noetic,melodic等
sudo apt install ros-<distro>-rqt
sudo apt install ros-<distro>-rqt-common-plugins
```

**计算图运行**

```
rosrun rqt_graph rqt_graph
# 第一个rqt_gtaph是包名，第二个是节点名称
```







# ROS通信机制

* 话题通信（发布订阅模式）
* 服务通信（请求响应模式）
* 参数服务器（参数共享模式）



## 话题通信

### 1.理论模型

话题通信是基于发布于订阅的形式的，也就是一个节点发布话题，另一个节点订阅话题，实现消息的发送于接收

作用：用于不断更新的，少逻辑处理的通信

**角色**

* ROS Master（大管家）
* Publisher(发布者)
* Subscriber（订阅者）



**流程**

发布者节点：

* 发布者发布话题（向大管家注册话题）
* 发布则组织发布的消息，并设置发布频率
* 发布者发布消息到话题当中

订阅者节点：

* 订阅者订阅话题并创建回调函数（向大管家注册要订阅的话题）

* 大管家按照话题进行匹配

* 在回调函数中处理接收到的消息

  

### 2.实现简单话题通信

**C++实现简单的发布者节点**

* 获取发布者对象

  ros::Publisher 发布者名称 = 大管家.advertise<发布消息类型>(话题名称，缓存长度)

* 发布者发布消息
  发布者名称.publish(消息对象)

* 发布消息频率控制
  获取对象：ros::Rate 名称（每秒发送多少条消息）
  控制频率：名称.sleep();

```c++
#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc,char* argv[])
{
    // 1.解决乱码问题
    setlocale(LC_ALL,"");
    
    // 2.节点初始化
    ros::init(argc,argv,"hello_pub_node");
    
    // 3.创建节点管家
    ros::NodeHandle nh;
    
    // 4.创建发布者对象
    ros::Publisher pub = nh.advertise<std_msgs::String>("hello",10);
    
    // 5.创建消息发布频率控制对象
    ros::Rate rate(10);
    
    // 6.获取消息对象
    int count = 0;
    std_msgs::String msg;
    
    while(ros::ok())
    {
        count++;
        ROS_INFO("发布者发布第%d条消息",count);
        
        // 6.组织消息
        msg.data = "hello";
        
        // 7.发布消息到话题中
        pub.publish(msg);
        
        // 8.频率控制
        rate.sleep();
        
        // 9.spinOnce回头处理循环中的回调函数（这里没有）
        ros::spinOnce();
    }
    
    return 0;

}
```

**C++订阅者的实现**

* 获取订阅者对象
  ros::Subscriber 订阅者名称 = 大管家.subscribe(话题名称，缓存长度，回调函数)
* 构造回调函数
  回调函数需要传入一个话题中消息同类型的参数

```c++
#include <ros/ros.h>
#include <std_msgs/String.h>

// ！回调函数一定是const类型
void hello_callback(const std_msgs::String& msg)
{
    // 打印接收到的消息
    ROS_INFO("接收到的消息是:%s",msg.data.c_str());

}

int main(int argc,char* argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello_sub_node");
    
    // 1.创建大管家
    ros::NodeHandle nh;

    // 2.创建订阅着对象
    ros::Subscriber sub = nh.subscribe("hello",10,hello_callback);

    // 3.回头查看消息处理回调函数
    ros::spin();

    return 0;
}
```

**出现的问题**：如果先启动订阅者节点，会因为没有接收到消息而挂起（spin()函数，译者再看哟有没有接收到消息而启动回调函数），任何再去启动发布者，但是也会造成前几条消息丢失的情况。因为发布者会先注册话题，但是有可能还没有注册成功就已经开始发消息了，而订阅者需要等话题注册成功后由大管家匹配完成话题中心，接收消息。
**解决：在注册后先进行休眠等待注册完成后再发布消息**

```c++
// 创建发布者对象，也就是向管家注册话题
 ros::Publisher pub = nh.advertise<std_msgs::String>("hello",10);
// 休眠3s
ros::Duration(3).sleep();
```



**python实现发布者**

* 获取发布者对象
  发布者名称 = rospy.Publisher(话题名称，消息类型，queue_size=缓存长度)

* 发布者发布消息

  发布者名称.publish(消息对象)

* 获取频率控制对象
  名称 = rospy.Rate(频率)

* 休眠

  rospy.sleep(时间s)

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    # 1.初始化
    rospy.init_node("hello_pub_node")
    
    # 2.创建发布者对象
    pub = rospy.Publisher("hello",String,queue_size = 10)
    
    # 3.创建频率控制对象
    rate = rospy.Rate(10)
    
    # 4.获取消息对象
    count = 0
    msg = String()
    
    # 5.休眠等待发布者注册成功
    rospy.sleep(3)
    
    while not rospy.is_shutdown():
        count += 1
        
        # 6.组织消息
        msg.data = "hello" + str(count)
        
        # 7.发布消息
        pub.publish(msg)
        
        # 8.控制频率
        rate.sleep()
        
        # 9.打印相关信息
        rospy.loginfo("发布的消息：%s",msg.data)
```

**python实现订阅者**

* 获取订阅者对象
  订阅者名称 = rospy.Subscriber(话题名称，消息类型，回调函数，queue_size=缓存长度)

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
from std_msgs.msg import String

# 回调函数
def hello_callback(msg):
    rospy.loginfo("接收到的消息：%s",msg.data)
    
if __name__ == "__main__":
    # 1.初始化
    rospy.init_node("hello_pub_node")
    
    # 2.获取订阅者对象
    sub = rospy.Subscriber("hello",String,hell_callback,queue_size=10)
    
    # 3.回头
    rospy.spin()
```



**解耦合**
不同的节点可以使用不同的代码语言来实现，例如再话题通信中，可以使用C++编写发布者代码，PYTHON编写订阅方。再ros中启动这两个节点也是可以的，不管是什么语言



### 3.自定义消息包

std_msgs封装了一些原生的数据类型，例如String,Int32,Int64,Char,Float32,float64,Bool,Empty.....但是这些数据只包含了一个data数据，结构单一，具有一定的局限性，无法传输一些比较复杂的数据。那么自定义消息包就可以船夫复杂的数据，类似于C语言中的结构体。

ROS还有一种特殊的消息类型;Header,标头包含**时间戳stamp**,**坐标系信息等等（frame_id）**

**流程**：

* 按照一定格式创建msg文件
* 编辑配置文件
* 编译生成可以被C++/Python调用的中间文件



**1.定义msg文件**

再功能包下创建一个msg文件夹，里面添加自定义消息的文件，文件内部定义该消息包含有的的消息类型

创建一个person.msg

```
string name
uint16 age
float54 height
```

**2.编辑配置文件**

* 配置package.xml文件

  ```
  # 添加说明编译时所需要的消息生成依赖项
    <build_depend>message_generation</build_depend>
  # 添加说明编译运行时的消息运行依赖项
    <exec_depend>message_runtime</exec_depend>
  ```

* 配置CMakeList.txt文件

  * find_pacakge中添加message_generation依赖项
    编译该功能包需要的依赖项

    ```
    find_package(catkin REQUIRED COMPONENTS
      roscpp
      rospy
      std_msgs
      message_generation
    )
    ```

  * add_message_files中添加自定义的消息文件（50行）
    编译时会编译person.msg文件

    ```
    add_message_files(
      FILES
      person.msg
    )
    ```

  * generate_messages，本案例不需要修改只需要取消注释（71行开始）
    意味着编译自定义消息包时所依赖的消息包

    ```
    generate_messages(
      DEPENDENCIES
      std_msgs
    )
    ```

  * catkin_package,取消CATKINDEPENDS这一行，最后还要加上message_runtime
    和find_package对应，这里指如果运行这个功能包的时候需要的依赖项，而find_page里面的功能包又需要依赖catkin_package里面的功能包
    find_page:编译时候的依赖，出错则编译出错
    catkin_package：运行时的依赖，出错编译正常但运行出错

    ```
    catkin_package(
    #  INCLUDE_DIRS include
    #  LIBRARIES mymsgs
       CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
    #  DEPENDS system_lib
    )
    ```

**3.编译**

编译会生成一些中间文件

* C++
  存储在catkin_ws/devel/include/mymsg/person.h的C++头文件，里面定义了自定义消息的类型，以后如果想要使用自定义的消息类型时，就可以在C++代码中包含该头文件就可以使用了

* Python
  储存在catkin_ws/devel/lib/python3/mymsg/msg/_person.py的python模块，里面定义了自定义的消息类型这个类，类中包含了自定义消息类型成员

  ```python
  # 从mymsg.msg包中导入person类
  from mymsg.msg import person
  
  # 实例化person类
  p = person()
  
  # 访问消息成员
  p.name = "gmz"
  p.age = 20
  p.height = 200.9
  ```

  **其他的消息包其实都是一样的，通过把消息封装到一个类里面，通过实例化消息类对象之后给类对象成员消息赋值**



**4.vscode配置**

产生了中间文件，如果想要在节点中使用该消息包，需要包含该头文件或者模块，那么需要配置vscode，添加路径，让vscode能找到这个头文件/模块
**C++头文件路径配置**

* 打开.vscode文件夹
* 打开c_cpp_properties.json文件
* 在includePath中添加路径：/home/gmz/catkin_ws/devel/include/**
  这样时表示包含include文件下的全部内容

**python包路径配置**

* 打开.vscode文件夹
* 打开settings.json文件
* 在python.autoComplete.extraPaths中添加路径："/home/gmz/catkin_ws/devel/lib/python3/dist-packages"



**5.CMakeList.txt配置**

**C++使用自定义消息包CMakeList.txt文件的配置**
需要修改这个：

```
add_dependencies(mymsg_pub_node ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(mymsg_sub_node ${PROJECT_NAME}_generate_messages_cpp)
```

因为有的时候你编写了自定义.msg文件，但是没有编译，.cpp文件之间包含了该头文件并使用该自定义消息类型，由于编译器是先编译.cpp文件的，但是这个时候.msg文件没有编译，会报错，所以添加这行就避免了这样的错误

**python使用自定义消息包配置**



### 4.自定义消息包话题通信

**C++发布者实现**

```python
#include <ros/ros.h>
#include <mymsgs/person.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"mymsg_pub");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<mymsgs::person>("mymsg",10);

    ros::Rate rate(5);
    ros::Duration(2).sleep();

    int count = 0;
    mymsgs::person p;
    p.name = "甘明珍";
    p.age = 20;
    p.height = 200.5;

    while(ros::ok())
    {
        pub.publish(p);

        count++;
        ROS_INFO("发送第%d条数据",count);

        rate.sleep();
    }
    
    return 0;
}
```

**C++订阅者实现**

```c++
#include <ros/ros.h>
#include <mymsgs/person.h>

void msg_callback(const mymsgs::person p)
{
    ROS_INFO("接收到的消息：%s,%d,%.2f",p.name.c_str(),p.age,p.height);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"mymsg_sub_node");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("mymsg",10,msg_callback);

    ros::spin();

    return 0;
}
```



**python发布者实现**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
from mymsgs.msg import person

if __name__ == "__main__":
    rospy.init_node("mymsg_pub_node")

    pub = rospy.Publisher("mymsg",person,queue_size=10)

    rate = rospy.Rate(5)
    rospy.sleep(2)

    count = 0
    p = person()
    p.name = "gmz"
    p.age=18
    p.height = 200

    while not rospy.is_shutdown():
        p.age+=1
        pub.publish(p)
        count+=1
        rospy.loginfo("发布第%d条数据",count)
        rate.sleep()
```

**python订阅者**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
from mymsgs.msg import person

def mymsg_callback(p):
    rospy.loginfo("%s,%d,%.2f",p.name,p.age,p.height)

    
if __name__ == "__main__":
    rospy.init_node("mymsg_sub_node")

    sub = rospy.Subscriber("mymsg",person,mymsg_callback,queue_size=10)

    rospy.spin()
```









## 服务通信

### 1.理论模型

服务通信是基于**请求应答模式**的，是一种应答机制
一个节点A向另一个节点B发布请求，节点B处理请求并产生响应结果返回给A

服务通信更适用于有实时性要求并且具有一定的逻辑性的场景

* 发送请求：客户端Server
* 处理请求并返回响应：服务端Client
* 管理者ROS master
* 启动顺序：先启动服务端，在启动客户端



**流程**

* Server端在ROS master处注册自身信息（话题名称，IP地址）
* Client端在ROS master处注册所需要的服务信息（话题名称）
* ROS master根据话题进行匹配，将匹配成功结果发送给Client（话题相同，则发送服务端的IP给客户端）
* Client端通过这个IP地址向Server端发送请求
* Server端接收到请求，处理请求并产生响应

生活化：联通分公司在总部注册公司信息，是什么品牌（Topic），公司地址（IP），总部保存好注册信息。我办理了联通的卡，有问题了，打电话给总部要求售后，总部给我提供了我最近的分公司的联系方式和地址。我拿到联系方式之后，打电话给分公司要求解决问题，分公司根据问题给反映我处理结果。



ROS已经帮我们封装好了，不需要从头开始写代码，只需要关注几个信息：

* 话题的名称
* 服务端接收到请求后如何处理
* 客户端怎么请求数据，收到反映后如何处理
* 中间的数据载体（话题通信消息载体有固定的形式，在服务端也是一样的）



### 2.自定义服务消息srv

流程：

* 定义srv文件
* 编辑配置文件
* 编译生成中间文件



**定义srv文件**：
创建一个功能包，新建名称为srv的文件夹，用于保存自定义srv文件，在srv文件夹下创建.srv文件，用于定义在服务通信时的消息参数：.srv

```
# 客户端请求时发送的数据

---
# 服务端响应发送的数据

```

```
int32 num1
int32 num2
---
int32 sum
```

**编辑配置文件**

* 编辑package.xml
  和自定义消息包一样，需要添加：
  编译时的依赖：message_generation,运行时的依赖：message_runtime
  
  ```xml
  <build_depend>message_generation</build_depend>
  
  <exec_depend>message_runtime</exec_depend>
  ```
  
* CmakeList.txt

  * 修改find_package发生配置，添加依赖message_generation
    find_package是配置当前创建的软件包所依赖的其他软件包，编译时的依赖项

    ```cmake
    find_package(catkin REQUIRED COMPONENTS
      roscpp
      rospy
      std_msgs
      message_generation
    )
    ```

  * 找到server相关配置：add_server_file
    是配置要产生服务的srv文件,这样在编译的时候会去编译自定义的.srv文件，产生中间文件放置在devel中，包含到时候调用该服务需要的头文件/模块

    ```
    add_service_files(
      FILES
      addserver.srv
    )
    把里面的文件名称改为自己创建的.srv文件名称
    ```

  * 添加依赖generate_message
    配置添加自定义srv文件里面包含的数据类型所依赖的消息包

    ```
    generate_messages(
      DEPENDENCIES
      std_msgs
    )
    ```

  * catkin_package
    编辑程序运行时的依赖项，和find_package有一点区别
    
    ```
    catkin_package(
    #  INCLUDE_DIRS include
    #  LIBRARIES server_pkg
      CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
    #  DEPENDS system_lib
    )
    ```

**最后ctrl shift b编译，生成中间文件**

这个时候就会生成该服务所需要的CPP头文件和python所需要的库文件，放在devel文件夹中（编译产生的中间文件存储位置）

**这个中间文件包括xx.h，xxResquest.h，xxResponse.h**，在需要该服务的节点中需要包含该xx.h头文件，里面定义了服务时请求的对象还有响应对象，对象内部封装了请求和响应需要的消息

编译后的.srv文件会产生到时候调用该服务的头文件/模块，节点导入该头文件/模块之后才能正常运行服务。这个头文件定义了服务的类对象，这个类对象里面还包含类成员Request和Response这两个类，类中又包含成员：请求的信息和响应的信息。



### 3.实现简单的服务通信

cpp流程：

* 服务端实现

  * 包含头文件
  * 初始化ROS节点
  * 获取大管家
  * 创建服务端对象
    类型为**ros::ServiceServer**，通过大管家**nh.advertiseService(Topic,回调函数)**获取
  * 处理请求产生响应（构造回调函数）
    需要犬儒参数为请求和响应的对象，例如本案例的**请求对象server_pkg::addint::Request& request**，**响应对象server_pkg::addint::Response& response**。回调函数返回值类型为布尔类型
  * spin

* 客户端实现

  * 包含头文件
  * 初始化ROS节点
  * 创建大管家
  * 创建客户端对象
    类型为**ros::ServiceClient**，通过大管家**nh.serviceClient< server-class>(Topic)**获取
  * 获取服务对象，发送请求
    以本案例为例，获取服务对象**server_pkg::addint ai**，服务对象下有成员请求和响应对象，通过服务对象调用请求和响应对象
  * 使用client.call(服务对象)查看是否被服务端成功处理请求并产生响应
  
* 配置文件
* 编译运行



**cpp服务端实现**

```c++
#include <ros/ros.h>
#include "server_pkg/addint.h"

/*
服务端实现：
    1.包含头文件
    2.初始化
    3.获取大管家
    4.创建服务对象
    5.处理请求并响应
    6.spin()
*/

// 服务端的回调函数
// 参数：请求对象，响应对象
bool donums(server_pkg::addint::Request& rq,
            server_pkg::addint::Response& rp)
{
    // 1.处理请求
    int num1 = rq.num1;
    int num2 = rq.num2;
    ROS_INFO("收到的请求数据：num1：%d,num2:%d",num1,num2);

    // 2.组织相应
    int sum = num1 + num2;
    rp.sums = sum;
    ROS_INFO("处理后的数据sum:%d",sum);

    return true;
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"complish_server_node");
    ros::NodeHandle nh;

    // 创建服务对象
    // 使用adevtiseServer(话题，回调函数)；
    // 返回值是布尔类型，看是否处理成功，回调函数用于处理请求
    ros::ServiceServer server = nh.advertiseService("/addint",donums);

    // 回头，一直查看是否又请求，处理回调函数
    ros::spin();
    return 0;
}
```

```c++
// 请求处理的回调函数
// 1.返回值是布尔类型
// 2.传入的参数是服务的请求对象和响应对象
bool donums(server_pkg::addint::Request& request,server_pkg::addint::Response& response)
{
    // 1.处理请求
    // 请求的对象里包含了两个消息
    int num1 = request.num1;
    int num2 = request.num2;
    
    // 2.组织响应
    // 以引用的方式传入响应对象，给它重新赋值，实参改变
    response.sums = num1+num2;
    ROS_INFO("处理后的数据sum:%d",sum);
    
    return true;
}
```

**cpp客户端实现**

```c++
#include <ros/ros.h>
#include "server_pkg/addint.h"
/*
	客户端：提交两个整数，并处理响应
		1.包含头文件
		2.setlocale，初始化
		3.创建大管家
		4.创建客户端对象
		5.提交请求并处理响应
*/
int main(int argc, char *argv[])
{
    // 2.setlocale，初始化
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"server_sub_node");
    
    // 3.创建大管家
    ros::NodeHandle nh;

    // 4.创建客户端对象
    ros::ServiceClient client = nh.serviceClient<server_pkg::addint>("/addint");

    // 5.提交请求并处理响应
    // 5-1.组织请求

    // 获取服务对象
    server_pkg::addint ai;
    // 获取服务请求对象
    ai.request.num1 = 1;
    ai.request.num2 = 2;

    // 5-2.处理响应

    // 客户端对象通过call函数查看是否成功处理请求
    bool flag = client.call(ai);
	
    // 针对是否成功处理来处理响应
    if(flag)
    {
        ROS_WARN("客户端接受响应");
        ROS_INFO("响应sums = %d",ai.response.sums);
    }
    else
    {
        ROS_WARN("客户端响应失败");
    }
    
    return 0;
}
```



**优化**

上面的案例中，请求的信息是已经被写死了，但是通常都是参数动态提交

1.在启动节点的时候,获取命令中的参数，并组织进request

2.格式：rosrun xxx xxxxx num1 num2

```
argc:代表传入参数的个数
argv：以字符串形式存储传入的参数
```

```c++
#include <ros/ros.h>
#include "server_pkg/addint.h"

int main(int argc, char *argv[])
{
    // argc:代表传入参数的总数量
    // 本案例共三个参数：程序名称，num1,num2
    if(argc != 3)
    {
        ROS_WARN("传入参数个数不对！");
        return 0;
    }

    setlocale(LC_ALL,"");
    ros::init(argc,argv,"server_sub_node");
    ros::NodeHandle nh;

    // 4.创建客户端对象
    ros::ServiceClient client = nh.serviceClient<server_pkg::addint>("/addint");

    // 5.提交请求并处理响应
    // 5-1.组织请求

    // 获取服务对象
    server_pkg::addint ai;
    // 获取服务请求对象
    // atoi转为int类型
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);

    // 5-2.处理响应

    // 客户端对象通过call函数查看是否成功处理请求
    bool flag = client.call(ai);

    if(flag)
    {
        ROS_WARN("客户端接受响应");
        ROS_INFO("响应sums = %d",ai.response.sums);
    }
    else
    {
        ROS_WARN("客户端响应失败");
    }
    
    return 0;
}
```

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\服务端参数动态提交.png)



**如果先启动客户端会抛出异常，但是有时候我们可以设置成等待服务端启动的模式**

也就是掀起的客户端，程序不会抛出异常，而是挂起，等待服务端启动，等服务端启动后，客户端正常请求服务

```
/*
ROS早意识到这个问题，内置了该相关函数
1.判断服务器状态函数：
	通过客户端对象：client.waitForExistence();
	通过ros中server下的函数：ros::server::waitForService(被等待的服务名称)
2.用处：在组织好请求之后，处理响应前	
*/
```



**PYTHON服务端实现**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
from server_pkg.srv import *

"""
    服务端：解析客户端请求，产生响应
        1.导包
        2.初始化
        3.创建服务端对象
        4.处理请求，产生响应
            回调函数
        5.spin()

"""

def donums(request:addintRequest):
    """
        1.参数：封装了请求数据
        2.返回值：响应数据
    """
    # 处理请求
    num1 = request.num1
    num2 = request.num2

    # 处理响应
    sums = num1 + num2

    # 获取响应对象
    response = addintResponse()
    response.sums = sums

    rospy.loginfo("服务器解析数据num1=%d,num2=%d",num1,num2)
    rospy.loginfo("响应数据sums=%d",response.sums)

    # 返回响应数据
    return response


if __name__ =="__main__":
    # 1.初始化
    rospy.init_node("server_pub_node")

    # 2.获取服务端对象
    server = rospy.Service("/addint",addint,donums)

    # 3.回头
    rospy.spin()
```

**python客户端实现**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
from server_pkg.srv import*

if __name__ == "__main__":
    # 初始化
    rospy.init_node("server_sub_node")
    
    # 获取客户端对象
    client = rospy.ServiceProxy("/addint",addint)

    # 组织请求，获取响应
    response = client.call(12,34)

    # 处理请求
    rospy.loginfo("响应的数据sums=%d",response.sums)
```

```
使用client.call()，传入的参数为请求的数据，使用该函数后会发送请求给服务端，服务端处理请求并常升响应，在服务端代码实现时，返回值为响应的对象，所以调用该函数后相当于调用请求的回调函数，返回了响应对象，在客户端这边就要接收返回的响应对象
```

**配置**

* chmod +x添加可执行权限

* 打开CmakeList文件，169~172行，catkin_install_python

  ```
  catkin_install_python(PROGRAMS
    scripts/server_pub_node.py
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )
  catkin_install_python(PROGRAMS
    scripts/server_sub_node.py
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )
  ```

* 编译

* 先启动服务端在启动客户端



**优化实现：动态提交参数，客户端挂起等待服务端启动**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
from server_pkg.srv import*
import sys

if __name__ == "__main__":
    # 优化实现，参数的动态提交
    # 需要包含库文件sys

    # 判断传入的参数个数
    if len(sys.argv) != 3:
        rospy.loginfo("传入参数个数不对！")
        sys.exit(1)


    # 初始化
    rospy.init_node("server_sub_node")
    
    # 获取客户端对象
    client = rospy.ServiceProxy("/addint",addint)

    # 组织请求，获取响应
    num1 = int(sys.argv[1])
    num2 = int(sys.argv[2])

    # 优化实现
    # 2.客户端挂起
    # 2-1通过客户端对象挂起
    client.wait_for_service()

    # 2-2 通过rospy挂起
    # 传入的参数是要等待的服务话题
    rospy.wait_for_service("/addint")
    
    response = client.call(num1,num2)

    # 处理请求
    rospy.loginfo("响应的数据sums=%d",response.sums)
    
```









## 参数服务器

### 1.理论模型

参数服务器在ROS中主要用于**实现不同节点之间的数据共享**，参数服务器相当于一个独立于所有节点的公共容器，可以将数据存储在该容器当中，被不同的节点调用，不同的节点也可以往其中存放数据

**概念**：以共享的方式实现不同节点之间的数据交互通信模式

**作用**：存储一些多节点共享的数据，类似全局变量

涉及到的三个角色·：

* ROS Master(管理者)
* Talker（参数设置者）
* Listener（参数调用者）

Talker提交参数，ROS Master将参数保存到参数服务器公共容器的参数列表当中，Listener向ROS Master发送请求，ROS Master在参数列表中寻找对应的参数值，并返回Listener

**参数服务器使用RPC，并不是高性能，最好存储静态的非二进制简单数据**

* int（4个字节的整型数据）
* double
* bool
* strings
* list
* dict
* iso8601 dates与时间相关的数据



### 2.参数操作

需求：实现参数服务器的增删改查操作

在c++中实现该操作，可以通过两套API

* ros::NodeHandle
* ros::param



**查看参数服务器参数列表：rosparam list**

```
rosparam list
```

**查看参数具体的值：rosparam get 参数名**

```
rosparam get 参数名
```



**CPP实现参数增加与修改**

```c++
#include <ros/ros.h>

/*
    实现参数的新增与更改
    需求：先设置机器人的共享参数，类型，半径，然后修改
    实现：
        1.ros::NodeHandle
            setParam()
        2.ros::param
            set()
*/

int main(int argc, char *argv[])
{
    // 1.初始化
    ros::init(argc,argv,"setparam_node");

    // 2.创建ros大管家
    ros::NodeHandle nh;

    // 3.新增参数
    // 3-1.ros::NodeHandle
    // nh.setParam(参数名，参数值)
    nh.setParam("type","smartrobot");
    nh.setParam("radius",0.15);

    // 3-2.ros::param
    // ros::param::set("type","smartrobot");
    // ros::param::set("radius",0.15);
    
    return 0;
}

```

**通过CPP代码实现参数的获取**

```c++
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
```

**CPP删除参数**

```c++
#include <ros/ros.h>

/*
    参数的删除
        1.nh
            deleteParam(name)
            返回值bool类型，看是否删除成功
        2.ros::param
            del()

*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"delparam");
    ros::NodeHandle nh;

    // 1.nh.deleteParam(name)
    bool flag = nh.deleteParam("radius_param");

    // 2.ros::param::del(name)
    bool flag2 = ros::param::del("radius");

    if(flag)
    {
        ROS_INFO("删除参数成功");
    }
    else
    {
        ROS_INFO("删除参数失败");
    }

    return 0;
}
```





**python增加修改参数**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy

if __name__ == "__main__":
	rospy.init_node("setparam")
    
    # 新增参数
    # rospy.set_param(参数名称，参数值)
    rospy.set_param("type","yellowcar")
    rospy.set_param("radius",0.5)
    
    # 参数的修改
    rospy.set_param("radius",0.1)
    
```

**python参数获取**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
"""
    rospy.get_param(参数名称,默认值)
    rospy.get_param_cached(参数名称，赋值)
    rospy.get_param_name()
    rospy.has_param(参数名称)
    rospy.search_param()

"""

if __name__ =="__main__":
    rospy.init_node("getparam")

    # 1.获取参数对应的值，不存在则返回默认值
    radius = rospy.get_param("radius",0)

    # 2.从缓存中获取参数对应的值，不存在则返回默认自
    radius2 = rospy.get_param_cached("radiuss",0)
    
    # 3.获取参数服务器所有参数
    names = rospy.get_param_names()

    for name in names:
        rospy.loginfo("获取到的键：%s",name)

    # 4.判断某个参数是否存在
    flag = rospy.has_param("type")
    if flag:
        rospy.loginfo("参数存在")
    else:
        rospy.loginfo("参数不存在")

    # 5.查找参数，返回值是返回存在的参数，不存在则为空
    key = rospy.search_param("noexist_param")
    rospy.loginfo("找到的参数key=%s",key)
    # 找到的参数key=None
  
```

**python删除参数**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
"""
    rospy.delte_param(参数名称)
    参数存在删除成功，参数不存在则会抛出异常

"""

if __name__ =="__main__":
    rospy.init_node("delparam")

    # 删除参数
    try:
        rospy.delete_param("hhh")
    except Exception as e:
        rospy.loginfo("被删除的参数不存在")
```







# 常用命令

* rosnode  操作节点
* rostopic  操作话题
* rosservice  操作服务
* rosmsg  操作消息
* rossrv  操作srv消息
* rosparam  操作参数
* roslaunch  操作launch文件

作用：与文件系统操作命令不同，文件操作系统命令时静态的，操作的时硬盘上的文件，而上诉命令时动态的，在ROS程序启动后可以动态的获取运行中的节点或者参数的相关信息



**操作后缀：**

* 在后面加上-h，相当于-help，查看命令的使用规则

  ```
  rosnode -h
  
  rosnode is a command-line tool for printing information about ROS Nodes.
  
  Commands:
  	rosnode ping	test connectivity to node
  	rosnode list	list active nodes
  	rosnode info	print information about node
  	rosnode machine	list nodes running on a particular machine or list machines
  	rosnode kill	kill a running node
  	rosnode cleanup	purge registration information of unreachable nodes
  
  Type rosnode <command> -h for more detailed usage, e.g. 'rosnode ping -h'
  ```

  查看具体命令使用规则

  ```
  rosnode ping -h
  
  Usage: rosnode ping [options] <node>
  
  Options:
    -h, --help  show this help message and exit
    -a, --all   ping all nodes
    -c COUNT    number of pings to send. Not available with --all
  ```

  

## rosnode

```
rosnode ping		测试节点的连接状态
rosnode list		列出活动的节点
rosnode info		打印节点信息
rosnode machine		列出指定设备上的节点
rosnode kill		杀死某个节点
rosnode cleanup		清除不可连接的节点
```

## rostopic

```
rostopic echo		打印信息到屏幕
rostopic hz			显示主题的发布频率
rostopic info		显示主题的相关信息
rostopic list		显示所有活跃的主题名称
rostopic pub		将数据发布到主题
rostopic type		打印主题类型
rostopic bw			展示主题使用的带宽
rostopic delay		显示待遇header的主题延迟
rostopic find		根据类型查找主题
```

## rosservice

```
rosservice args		打印服务参数
rosservice call		使用提供的参数调用服务
rosservice find		按服务类型查找服务
rosservice info		打印有关服务的消息
rosservice list		列出所有活跃的服务
rosservice type		打印服务类型
rosservice uri		打印服务的ROSRPC uri
```

```
rosservice call 服务名称 请求参数
相当去客户端的实现，使用该命令调用某个服务，同时需要向里面传入服务的请求参数，回车后显示的时响应的参数结果
```

```
rosservice info 服务名称
打印该服务的相关信息：1.Node:所在的节点名称 2.URI:服务的地址 3.Type：服务消息的类型 4.Args：服务消息中的参数
```



## rosmsg

```
rosmsg show			显示消息描述
rosmsg info			显示消息描述
rosmsg list			列出所有消息（ros下的所有消息包）
rosmsg package		显示某个功能包下的所有消息
rosmsg packages		列出包含消息的功能包
rosmsg mds			显示mds加密后的消息
```

```
rosmsg show/info 消息包
显示该消息包下所有的消息参数

rosmsg show geometry_msgs/PointStamped
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
geometry_msgs/Point point
  float64 x
  float64 y
  float64 z
```

## rossrv

```
rossrv show				显示服务消息描述
rossrv info				显示服务消息描述
rossrv list				列出所有服务消息（ros下的所有消息包）
rossrv package 包名	   显示某个包下的所有服务消息
rossrv packages			列出包含服务消息的功能包
rossrv mds				显示mds加密后的服务消息
```

## rosparam

```
rosparam set		设置参数
rosparam get		获取参数
rosparam load		从外部文件加载参数
rosparam dump		将参数写到外部文件
rosparam delete		删除参数
rosparam list		列出所有参数
```

```
// 添加参数到参数服务器
rosparam set 参数名称 参数值
// 获取参数值
rosparam get 参数名称
// 删除某个参数
rosparam delete 参数名
// 列出当前ros中的参数
rosparam list
```



# TF坐标变换

机器人有很多传感器，激光雷达，摄像头等等。通过摄像头明确障碍物与摄像头间的位置关系，但实际上我们想知道机器人底盘与障碍物间的空间位置，我们不能直接将摄像头坐标系与障碍物位置坐标等同于底盘与障碍物间的位置关系，需要进行坐标系转换。

明确了不同坐标系之间的相对位置关系，就可以计算任何坐标点在不同坐标系中的位置，这个转换时经常要用到的，但算法实现较为复杂，ROS就封装了这个模块：坐标变换TF

**TF就实现了这样的功能：坐标点在不同坐标系下的转换**

**tf2功能包**

* tf2_geometry_msgs：可以将ROS消息转为tf2消息
  ROS消息就是平时我们在msg写的消息包，但是通常会转成tf2消息，实现更高效坐标转换
* tf2：封装了坐标变换常用消息
  例如四元数与欧拉角的转换
* tf2_ros：为tf2提供了rospy,roscpp绑定，封装了坐标变换常用的API
  平时都是使用ROS大管家来进行发布者订阅者的创建，tf2进一步把他封装起来，用tf2_ros内的管家来创建tf2坐标变换相关的发布者和订阅者





## ROS的坐标消息msg

**1.物体在坐标系下的位置关系**

**geometry_msgs/PointStamped**

```
std_msgs/Header header
  uint32 seq			// 序列号（不需要关注）
  time stamp			// 时间戳
  string frame_id		// 指以哪个坐标系为参考系
  
geometry_msgs/Point point
  float64 x				// 相对于参考坐标系的位置关系
  float64 y
  float64 z

```

**2.坐标系间的相对位置**

**geometry_msgs/TransformStamped**

```
std_msgs/Header header
  uint32 seq			// 序列号（不需要关注）
  time stamp			// 时间戳
  string frame_id		// 被参考系（父坐标系）
  
string child_frame_id	// 子坐标系

geometry_msgs/Transform transform		// 描述两者关系
  geometry_msgs/Vector3 translation		// x,y,z三个坐标轴上的偏移量
    float64 x
    float64 y
    float64 z
  geometry_msgs/Quaternion rotation		
  // x,y,z三个轴上的角度偏移量（四元数形式）可以看作欧拉角的另一种形式
  // 通常需要使用欧拉角于四元数的转换（tf2中封装了该转换的函数）
    float64 x
    float64 y
    float64 z
    float64 w
```





## 静态坐标变换

**依赖项：**

* rospy
*  roscpp
*  tf2 
*  tf2_ros
*  tf2_ros_geometry_msgs
*  geometry_msgs



**TF中的静态坐标发布者<tf2_ros/static_transform_broadcaster.h>**

**TF中坐标订阅者<tf2_ros/transform_listener.h>**



### 1.编辑两坐标系相对位置关系

流程：

* 发布节点，编辑两个坐标系的相对位置关系，将消息发布
* 订阅方节点，订阅两个坐标系相对位置关系的话题，获取相关信息，编辑坐标点信息，借助tf实现坐标变换

**本质上就是一个话题通信，将两个坐标系的相对位置关系发布出去**



**C++**:

```c++
#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

/*
包含的头文件
1.ros/ros.h
2.geometry_msgs/TransfrmStamped.h
    设置两坐标相对位置关系的消息宝

3.tf2_ros/static_transform_boardcaster.h
    tf静态坐标发布的广播系统，用于创建发布静态坐标系消息的发布者
    注意tf以及把发布者，发布话题的步骤封装起来了，只需要调用tf的发布者就可以实现nodehandle大管家创建发布者同时创建话题/tf_static，最后调用发布消息后也会把组织好的消息发到话题中

4.<tf2/LinearMath/Quaternion.h>
    用于使用欧拉较转变为四元素
*/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_pub");

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

    // 进入循环
    ros::spin();

    return 0;
}
```

**PYTHON**

```python
#!/usr/bin/env python3
#conding=utf-8

import rospy
import tf2_ros
from geometry_msgs.msg import TransformStamped
import tf

if __name__ == "__main__":
    # 初始化操作
    rospy.init_node("static_pub_node")
    
    # 获取发布对象
    pub = tf2_ros.StaticTransformBroadcaster()

    # 组织发布信息
    msg = TransformStamped()
    # 父坐标系
    msg.header.frame_id = "base_link"
    # 时间戳
    msg.header.stamp = rospy.Time.now()
    
    # 子坐标系
    msg.child_frame_id = "laser"
    
    # xyz偏移量
    msg.transform.tanslation.x = 2.0
    msg.transform.tanslation.y = 0.0
    msg.transform.tanslation.z = 0.5
    
    # 欧拉数与四元数转换
    # python中获取四元数对象是通过tf下的transformation.quation_from_euler函数，直接传入欧拉角
    # 传入欧拉角获取四元数对象
    qnt = tf.transformations.quation_from_euler(0,0,0)
    # 获取对应的四元数进行赋值操作
    msg.transform.rotation.x = qnt[0]
    msg.transform.rotation.y = qnt[1]
    msg.transform.rotation.z = qnt[2]
    msg.transform.rotation.w = qnt[3]

    # 发布数据
    pub.sendTransform(msg)

    rospy.spin()

```

**本质上就是一个话题通信，将两个坐标系的相对位置关系发布出去**

当你运行了这个节点之后，rostopic list查看，发现多了一个话题/tf_static
使用rostopic ehco /tf_ststic可以查看你面发布的消息

```
transforms: 
  - 
    header: 
      seq: 0
      stamp: 
        secs: 1738824928
        nsecs:  96705330
      frame_id: "base_link"
    child_frame_id: "laser"
    transform: 
      translation: 
        x: 0.2
        y: 0.0
        z: 0.5
	rotation: 
        x: 0.0
        y: 0.0
        z: 0.0
        w: 1.0
```

使用rviz查看两个坐标系位置关系（可视化）

在Fixed Frame中选择以base_link作为主坐标系

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\static_tf相对位置.png)





### 2.实现静态坐标转换

**C++实现**

**buffer用处**

* 缓存器，用于储存订阅的消息（话题中所有的坐标相对位置关系）
* 提供坐标变换内置函数buffer.transform(坐标点，转换后的参考坐标系)，返回值时一个坐标点信息geometry_msgs/PointStamped
  但是该函数编译需要依赖tf2_geometry_msgs/tf2_geometry_msgs.h

```c++
// buffer提供了内置坐标转换函数
buffer.transform(要转换的坐标点，要转换后的参考坐标系);
// 因为转换的坐标点由frame_id信息，同时buffer里面缓存有接收到的由tf发布的消息，包括/tf_static话题中的两坐标系的静态相对位置关系，这样就可以实现转换操作。返回值是geometry_msgs/PointStamped,是坐标点做桓侯的坐标信息

// 要实现这个功能，要包含头文件tf2_geometry_msgs/tf2_geometry_msgs.h
```

```c++
#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char *argv[])
{
    // 设置编码，正常显示中文
    setlocale(LC_ALL,"");

    // 初始化
    ros::init(argc,argv,"static_sub_node");
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

    while(ros::ok())
    {
        // 核心算法：将相对于laser的坐标转换为相对于base_link的
        // 1.创建一个坐标点信息对象，用于接收转换操作后的坐标信息
        geometry_msgs::PointStamped ps_out;
        // 2.通过buffer内置转换函数实现转换
        ps_out = buffer.transform(ps,"base_link");

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

```

```
#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
```

**PYTHON**

```
此时，描述坐标点在坐标系中的位置要使用tf的信息格式，
也就是tf2_geometry_msgs中的PointStamped
信息格式和geometry_msgs/PointStamped一样，只是被封装到了tf2里面
```

```python
#!/usr/bin/env python3
#coding=utf-8

import rospy
import tf2_ros
from tf2_geometry_msgs import tf2_geometry_msgs

if __name__ == "__main__":
    # 1.初始化操作
    rospy.init_node("static_sub_node")

    # 2.tf创建监听者和缓存器
    buffer = tf2_ros.Buffer()
    sub = tf2_ros.TransformListener(buffer)

    # 3.组织要转换的坐标点
    ps = tf2_geometry_msgs.PointStamped()
    # 3-1.设置时间戳
    ps.header.stamp = rospy.Time.now()
    # 3-2.设置参考坐标系
    ps.header.frame_id = "laser"
	# 3-3.设置在坐标系中的位置
    ps.point.x = 2.0
    ps.point.y = 3.0
    ps.point.z = 5.0
	
    # 4.控制发布消息的频率
    rate = rospy.Rate(10)
    
    while not rospy.is_shutdown():
        try:
            # 5.坐标点的转换
            transps = buffer.transform(ps,"base_link")
            rospy.loginfo("转换后的坐标：(%.2f,%.2f,%.2f)",
                        transps.point.x,
                        transps.point.y,
                        transps.point.z)
            
        except Exception as e:
            rospy.logwarn(e)
        
        rate.sleep()
```



**对于静态坐标信息的发布，逻辑都是一样的，只需要修改父系坐标名称，子系坐标名称，x偏移量，y偏移量，z偏移量，x翻滚角度，y翻滚俯仰，z偏航角度就可以了，为了提高代码的复用性，ROS把静态坐标转换封装成了一个模块**，使用方法:

```
rosrun tf2_ros static_transform_publisher x偏移量 y偏移量 z偏移量 z偏航角度 y俯仰角度 x翻滚角度 父系坐标名称 子系坐标名称
```

这样就实现了静态坐标系相对信息的发布





## 动态坐标变换

动态坐标变换，也就是两个坐标系的相对位置是变换的。

简单案例：启动turtlesim_node，该节点中有一个世界坐标系（坐标系原点），乌龟是另一个坐标系，键盘控制乌龟的运动，同时将两个坐标系相对位置进行动态发布

分析：

* 乌龟本身不仅可以看作一个坐标系，也可以看作是世界坐标系中的一个坐标点
* 订阅turtle1/pose，可以获取乌龟在世界坐标系的x,y,z坐标，偏移量以及线速度和角速度
* 将pose信息转化成坐标系相对信息并发布



**实现流程**：

* 新建功能包，添加依赖
* 创建坐标相对位置关系发布方（同时需要订阅乌龟位姿信息）
* 执行，通过rviz可视化



**乌龟节点**

```
rosrun turtlesim turtlesim_node
```

**乌龟控制节点**

```
rosrun turtlesim turtle_teleop_key
```

**乌龟节点位姿话题/turtle1/pose**

```
$ rostopic list
/turtle1/pose

$ rostopic info /turtle1/pose
Type /turtlesim/Pose

$ rosmsg show /turtlesim/Pose

float32 x
float32 y
float32 theta					# 乌龟朝向
float32 linear_velocity			# 乌龟线速度
float32 angular_velocity		# 乌龟角速度
```



### 1.动态坐标系相对位置信息的发布

**C++发布动态坐标实现**

```
// 回调函数的参数是乌龟的位姿信息对象，需要的头文件：
#include <turtlesim/Pose.h>

// 动态坐标变换信息的发布对象为tf2_ros下TransformBroadcaster，需要头文件：
#include <tf2_ros/transform_broadcaster.h>
```

```c++
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
    qnt.setRPY(0,0,pose.theta);
    tfs.transform.rotation.x = qnt.getX();
    tfs.transform.rotation.y = qnt.getY();
    tfs.transform.rotation.z = qnt.getZ();
    tfs.transform.rotation.w = qnt.getW();

    // 发布对象
    pub.sendTransform(tfs);

}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"domatic_pub");
    ros::NodeHandle nh;

    // 创建订阅对象（订阅乌龟位姿话题）
    ros::Subscriber sub = nh.subscribe("/turtle1/pose",100,delPose);

    // spin()
    ros::spin();

    return 0;
}
```

**python实现**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
from turtlesim.msg import Pose
import tf2_ros
from geometry_msgs.msg import TransformStamped
import tf

def dopose(pose):
    # 1.创建动态坐标系信息对象
    pub = tf2_ros.TransformBroadcaster()

    # 2.组织坐标系相对位置信息
    # 获取信息对象
    tfs = TransformStamped()

    # 编辑表头
    tfs.header.frame_id = "world"
    tfs.header.stamp = rospy.Time.now()

    # 编辑子坐标
    tfs.child_frame_id = "turtlesim"

    # 编辑x,y,z偏移量
    tfs.transform.translation.x = pose.x
    tfs.transform.translation.y = pose.y
    tfs.transform.translation.z = 0

    # 欧拉角转四元数
    qnt = tf.transformations.quaternion_from_euler(0,0,pose.theta)
    tfs.transform.rotation.x = qnt[0]
    tfs.transform.rotation.y = qnt[1]
    tfs.transform.rotation.z = qnt[2]
    tfs.transform.rotation.w = qnt[3]

    # 信息发布
    pub.sendTransform(tfs)


if __name__ == "__main__":
    rospy.init_node("domatic_pub")

    # 1.创建订阅者，订阅/turtle1/pose话题
    sub = rospy.Subscriber("/turtle1/pose",Pose,dopose,queue_size=100)

    # 2.spin
    rospy.spin()
```



### 2.动态坐标变换的实现

**C++动态坐标变换实现**

```c++
#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/PointStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"domatic_sub");

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

    while(ros::ok())
    {
        // 3.坐标变化
        geometry_msgs::PointStamped ps_out;
        ps_out = buffer.transform(ps,"world");

        // 4.坐标变换后的展示
        ROS_INFO("该点相对于%s的坐标(%.2f,%.2f,%.2f)",
        ps.header.frame_id.c_str(),
        ps.point.x,ps.point.y,ps.point.y);

        ROS_INFO("该点相对于%s的坐标(%.2f,%.2f,%.2f)",
        ps_out.header.frame_id.c_str(),
        ps_out.point.x,ps_out.point.y,ps_out.point.y);

        rate.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
```

**python实现**

```python
#!/usr/bin/env python3
#encoding=utf-8

import rospy
import tf2_ros
from tf2_geometry_msgs import tf2_geometry_msgs

if __name__ =="__main__":
    rospy.init_node("domatic_sub")

    # 1.创建坐标系监听对象
    buffer = tf2_ros.Buffer()
    sub = tf2_ros.TransformListener(buffer)

    # 2.组织坐标点信息
    ps = tf2_geometry_msgs.PointStamped()

    ps.header.frame_id = "turtlesim"
    ps.header.stamp = rospy.Time(0.0)

    ps.point.x = 2.0
    ps.point.y = 2.0
    ps.point.z = 2.0

    # 3.坐标变化发布频率
    rate = rospy.Rate(1)
    rospy.sleep(2)

    while not rospy.is_shutdown():
        # 4.进行坐标变化
        ps_out = buffer.transform(ps,"world")

        # 5.展示变换后的坐标
        rospy.loginfo("坐标变换后(%.2f,%.2f,%.2f),参考坐标系为%s",
                      ps_out.point.x,
                      ps_out.point.y,
                      ps_out.point.z,
                      ps_out.header.frame_id)
        rospy.loginfo("坐标变换前(%.2f,%.2f,%.2f),参考坐标系为%s",
                      ps.point.x,
                      ps.point.y,
                      ps.point.z,
                      ps.header.frame_id)
        
        rate.sleep()
```



# launch文件

launch包含了很多标签

* launch  根标签
* node  节点标签
* include
* remap
* param
* rosparam
* group
* arg



流程：

* 新建功能包
* 功能包新建目录launch存放.launch文件
* 在launch文件夹下创建.launch文件
* 开始编辑内容



调用launch文件

* 启动roscore核心节点

* 新建终端，输入命令

  ```
  roslaunch 包名 launch文件名称.launch
  ```

**roslaunch命令执行launch文件时，会先判断有没有启动roscore，如果启动了则不再启动，如果没有启动会自动调用roscore启动核心**



## launch标签

< launch>标签是所有launch文件的根标签，充当其他标签的容器

**属性：弃用标签deprecated="提示消息"**

```xml
<launch deprecated="此文件已经过时，不建议使用！">

</launch>
```

如果启动弃用标签的的launch文件，还是可以使用，只是会在终端输出红色提示信息

其他标签都是卸载launch标签内部的，是子级标签



## node标签

**< node>标签用于指定ROS节点，是最常用的标签**

！注意：roslaunch命令并不能保证按照node的声明顺序来启动节点（节点的启动时多进程的）

```
# 当node标签内部没有子级标签时，以<node开头 />结尾
<node pkg="" type="" name="" />

# 当node标签内还有其他子级标签时,以<node>开头</node>结尾
<node pkg="".....>
	<param>..
</node>
```

**属性**

* pkg="包名"
  声明节点所属的包

* type="node Type"
  节点类型（与之相同名称的可执行文件）

* name="node name"
  节点名称（在ROS网络拓扑中的节点名称，也就是初始化时给节点的命名）

* args="xxx xxx xxx"(可选)
  将参数传递给节点，就像之前在给客户端在命令行中传递参数一样，每个参数用空格隔开

* machine="机器名称"（可选）
  在指定的机器上运行

* respawn="true | flase"（可选）
  如果节点退出，是否自动重启（例如无人车的雷达节点，如果因为意外退出了，需要重新启动）

* respawn_delay="N"（可选）
  如果respawn为true,那么延迟N秒后重启

* required="true | false"
  如果为true,那么该节点退出时，将杀死整个roslaunch

* output="log | screen"（可选）
  日志发送目标，可以设置为log日志文件或者screen屏幕，默认log

* clear_param="true | false"（可选）

  在启动前，删除节点的私有空间的所有参数

* ns="xxx"（可选）

  在指定的命名空间xxx中运行节点

**子级标签**

* env环境变量参数
* remap重映射节点名称
* rosparam参数设置
* param参数设置



## include标签

< include>包含标签,用于将另一个xml格式的launch文件导入到当前的文件

**属性**

* fiind="$(find 包名)/xx/xx/xx.launch"

  ```
  <include find="$(find pakagename)/launch/xxx.launch"/>
  ```

  要包含的文件路径

* ns= "xxx"
  指定的命名空间导入文件

**子级标签**

* env环境变量设置
* arg将参数传递给被包含的launch文件



## remap标签

用于话题的重命名

**属性**

* from="xxx"
  原始的话题名称
* to="xxx"
  修改后的话题名称

**无子级标签**

```
<node>
	<remap from="xxx" to="xxx"/>
</node>
```



## param标签

< param>标签主要用于在参数服务器上设置参数，参数源可以在标签中通过value指定，也可以通过外部文件加载，在< node>标签中相当于私有命名空间

**属性**

* name="命名空间/参数名"
* value="xxx"（可选）
  定义参数值，如果此处省略，必须指定外部文件作为参数源
* type="str | int |double | bool | yaml"（可选）
  * 包含.的数字自动解析为double，否则int
  * "true"和"false"自动解析为bool
  * 其他为字符串

**无子级标签**

```
# 定义在<node>外部
<param name="paramA" type="double" value="3.14"/>

# 定义在<node>内部
<node pkg="mypkg" ......>
	<param name="paramB" type="double" value="5.14"/>
</node>

# 运行该launch文件后，通过rosparam查看参数服务器
/paramA
/mypkg/paramB
```



## rosparam标签



## arg标签

arg标签用于动态传参，类似于函数的参数，可以增强launch文件的灵活性

**属性**

* name="参数名称"
* default="默认值"（可选）
* value="数值"（可选）
* doc="描述"
  参数说明

**无子级标签**

用法：当设置参数时，有时候会给多个参数赋值同一个值，但是如果每个参数都独立设置，需要更改的时候就要每个都修改一遍

```
# A,B,C都使用同一个值，但是如果要修改，需要修改三个
<param name="A" value="0.5"/>
<param name="B" value="0.5"/>
<param name="C" value="0.5"/>
```

```
# 使用arg声明参数，到时候只需要修改arg就可以了
<arg name="car_size" default="0.5"/>

<param name="A" value="$(arg car_size)"/>
<param name="B" value="$(arg car_size)"/>
<param name="C" value="$(arg car_size)"/>
```



# 导航

## 导航模块简介

ROS中导航功能包为机器人导航提供了通用实现，开发者不需要关注复杂的导航实现算法以及硬件交互等等，这些只需要专业人员维护就可以了。开发者通过调用导航相关的功能包，传入不同的参数等实现开发。

**关键技术**

* 全局地图
  全局概览图（后续的定位和路径规划都需要）
* 自身定位
  确定自己在地图的哪个位置
* 路径规划
  全局路径规划+局部路径规划
  全局路径规划：大概的路径规划    局部路径规划：更精确的规划，躲避障碍物等等
* 运动控制
  控制速度和方向
* 环境感知
  感知周围的环境

生活案例：在公园中，我们想去某个地方，首先我们要获取到公园的全局地图，然后在全局地图中定位自己的位置在哪以及目标位置在哪，这就是自身定位，最后查看地图，进行路径规划，看选择什么样的路径去到目标地点。做好了路径规划，就要前进了，也就是运动控制，控制速度等等，前进。但是在不断前进的过程中也要不断的观察周边的环境，看看自己到达路径的哪个位置，是否要进行左拐右拐还是前进等等，这个也就是环境感知。
