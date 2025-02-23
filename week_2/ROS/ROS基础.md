## 环境搭建

### 模块化 分布式的系统

模块化编程

ros中每个launch文件相当于一个房子，每个node相当于房子的砖块，由多个node组装成一个launch



### ROS应用商店APT

APT就像手机的应用商店，可以通过APT取下载软件包

打开index.ros.org

点击packages list可以查看可以安装的软件包



### GitHub

官网https://github.com

有很多开源代码和ROS的软件包

这个软件包与APT软件包不同之处是github上的软件包以源代码的形式，需要编译之后才能使用。所以需要使用Git把github上的源代码下载下来之后编译

在用户文件夹中创建一个文件夹，专门用于储存下载下来的软件包

以下载wpr_simulation软件包为例

* 打开终端，创建一个文件夹 

  catkin_ws

  src:srouce资源，存放为编译的源代码

  ```
  mkdir catkin_ws
  cd catkin_ws
  mkdir src
  ```

* 下载git  （src子目录下）

  ```
  cd ~/catkin_ws/src
  sudo apt install git
  ```

这样一个工作空间就准备好了

* 克隆源码包（下载源码包）

  ```
  cd ~/catkin_ws/src
  git clone "源文件的网站"
  ```

这样就完成了下载

一个源码包包含了很多东西通常子目录scripts：包含脚本文件和python程序目录

ROS源码包中scripts通常存放依赖包，我们需要对源码进行编译才能使用，但是源码正常编译需要安装好依赖包，所以需要在编译运行前把依赖包安装好
![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\屏幕截图 2025-01-25 115736.png)

* 使用脚本安装依赖库
  在scripts子目录中打开终端（或者就是把当前目录切换到scripts）
  输入命令(打开脚本文件，安装对应的依赖库，noetic版本则选择noetic)：./install_for_noetic.sh

  ```
  cd ~/catkin_ws/src/scripts
  ./install_for_noetic.sh
  ```

所有依赖包安装完成后可以开始编译源代码

需要退回到工作空间的入口地址（~/worksapce)

* 运行catkin_make开始编译src中所有源代码

  ```
  cd ~/catkin_ws
  catkin_make
  ```

此时所有src中的源代码都编译完成了，可以开始使用软件包中的功能了
但是要先把工作空间的环境参数加载到终端，否则在运行的时候会找不到这写软件包，则无法正常使用这些功能

* 使用source指令载入工作空间的环境参数

  ```
  （在工作空间入口处运行该指令）
  source ~/catkin_ws/devel/setup.bash
  ```

* 使用roslaunch运行编译好的ROS程序

  ```
  roslaunch wpr_stimulation wpb_simple.launch
  ```



* 将source工作空间环境配置指令写入终端程序初始化脚本程序.bashrc

  ```
  gedit ~/.bashrc
  
  滑到脚本文件最下面，添加：
  source ~/catkin_ws/devel/setup.bash
  
  （在source /opt/ros/noetic/setup.bash下方）
  ```

  






### Terminator超级终端

ROS通常需要多个终端窗口，而ubuntu自带的终端窗口需要重建，不方便，超级终端窗口可以通过水平分割将多个终端窗口放在一起更方便管理

快捷键：

ctrl+alt+t：打开terminator

ctrl + shift + e :左右分频

ctrl + shift + o:水平分频

ctrl + shift + w:删除当前窗口



ctrl+shift+e分频失败原因：ubuntu系统提前设置了这组快捷键方式，可以将其删除

* 在终端输入ibus-setup
* 选择表情符号页面
* 删除该快捷键



### ROS index网站

以后查ROS软件包等各种资源时，可以用这个网站去查相关信息

**index.ros.org/search**





## 工作空间

### 概念

workspace:存放工程文件的文件夹

* workspace
  * build：编译过程产生的中间文件
  * src：代码文件
  * devel：编译生成的目标文件

### 创建工作空间

* 创建文件夹mkdir -p ~/catkin_ws/src
* 进入文件夹cd ~/catkin_ws/src
* 初始化catkin_init_workspace
* 返回上一级目录（工作空间入口）cd ..
* 编译工作空间catkin_make
  * catkin_make是编译工作空间中所有的功能包
  * catkin_make -DCATKIN_WHITELIST_PACKAGES="package_name"是编译指定的软件包

### 添加环境变量

**目的是告诉系统这是我们工作空间的一个路径，这样我们在运行里面的程序的时候才能够倍正确的索引**

所以在运行里面的程序时，需要在工作空间入口执行**sour devel/setup.bash**指令
但是这种方法具有局限性，只在这个终端窗口起作用，把他添加成全局变量会更方便。

编写.bashrc文本，在末尾添加**sour 工作空间路径/devel/steuo.bash**，保存退出后在终端输入命令sour .bashrc就可以了。

* vim .bashrc
* 编写.bashrc文本



## 功能包

存放在工作空间中的src文件夹中

包含内容：

* include：.h文件
* src：.cpp文件
* launch：launch文件
* urdf：.urdf文件
* scripts：可执行脚本文件（python）
* CMakeList.txt：定义编译规则
* package.xml：定义package的属性
* config：参数文件（yaml,srv,msg,action）

**创建功能包：catkin_create_pkg pkg_name dependen1.....**





## CMakeList.txt

作用：定义编译规则

常用的cmakelists宏：

* cmake_minimum_required()  CMake版本
* project()    项目名称
* find_package()    添加依赖
* catkin_package()    编译生成信息导出
* add_execuatable()    生成可执行文件
* target_link_libraries()    可执行文件链接到库



## python代码与cpp代码

对于cpp代码，要使得其编译成功，需要在该功能包目录下的CmakeList.txt文件中添加编译规则

* add_executable() 生成源代码的可执行文件
  CmakeList.txt文件第136行

  ```
  add_executable(${PROJECT_NAME}_node src/server_param_pkg_node.cpp)
  add_executable(可执行文件的名称 src/源代码.cpp文件的名称)
  add_executable(main src/main.cpp)
  ```

* target_link_libraries()    可执行文件链接到库
  156行

  ```
  target_link_libraries(源代码名称
    ${catkin_LIBRARIES}
  )
  ```



对于python，要使得可以运行，需要为该源代码添加可执行权限，任何在工作空间入口进行catkin_make编译/或者在CmakeList.txt中添加编译规则

* 在终端中打开，chmod +x xx.py

* catkin_install_python
  162

  ```
  # catkin_install_python(PROGRAMS
  #   scripts/my_python_script
  #   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  # )
  catkin_install_python(PROGRAMS
    scripts/源代码.py文件名称
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )
  ```

  





## ROS

### Node节点和Package包

大致流程：

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\软件包创建流程.png)

**创建package包**

* 打开终端，将进入~/catkin_ws/src目录
* 输入 catkin_create_pkg ssr_pkg rospy roscpp std_msgs创建包
  * catkin_create_pkg <包的名称> <依赖项列表>
    c此时创建了一个名为ssr_pkg的软件包，依赖软件包rospy roscpp std_msgs
  * **依赖项**：在对节点进行组织划分的时候，一般吧关系比较密切的放在同一个包里，但实际上有一些节点的通用性比较强，会同时很多软件包的节点发生关联，放在哪个都不合适，所有把这些节点单独放在一个包里，谁要用谁就去依赖这个包
  * 回访依赖包：使用指令roscd <包的名称>即可进入这个依赖包的目录，ls查看包的文件，使用code package.xml可打开该包的代码文件，查看依赖包信息
    **package.xml**是软件包的必备项目，所以当看到一个文件里有package.xml可认为是一个软件包

**/opt/ros/noetic/share**目录下的都是软件包，这些软件包来源于港式安装ros是的基础包，其他是通过APT下载的软件包，这些软件包都是现成的可执行文件，已经编译好的程序，可以直接运行

**~/catkin_ws/src**是我们自己创建的存储源码包地址，这些是通过github下载的软件包，没有经过编译是不可以直接运行的

这时可以联想到当时将source工作空间环境配置指令写入终端程序初始化脚本程序.bashrc

```
source /catkin_ws/devel/setup.bash
source /opt/ros/noetic/setup.bash
```

也就是说我们使用的依赖包必须是在这两个路径下的软件包，否则执行的时候会找不到，则会报错（相当于提供一个查找软件包的路径，在这些路径下查找软件包，如果你设置的软件包不在这两个路径下则会报错）
路径：/opt/ros/noetic/share    ~/catkin_ws/src



**创建Node节点**

* 打开vs code,在目标软件包的src文件下新建一个cpp文件(chao_node.cpp)

* #include <ros/ros.h> 库文件

* main(按TAB自动补全)

* 源码编译：

  * 打开该src下的CMakelist.txt文件，为新建你的节点编译提供规则

  * 找到Build这个章节

    ```
    ###########
    # Build	  #
    ###########
    ```

  * 找到Declare a C++ executable这一节，中间两行是对这一指令的解释，最后一行是C++可执行文件编译的指令（代码注释两个##表示对代码的解释，一个#表示代码）

  * 复制该指令，粘贴到该文件最后一行（不保留#）,修改后ctrl+s保存

    ```
    add_executable(${PROJECT_NAME}_node src/ssr_pkg_node.cpp)
    # PROJECT_NAME是新建节点的名称
    # 最后一段是指定从哪个代码文件进行编译
    
    add_executable(chao_node.cpp src/chao_node.cpp)
    ```

  * ctrl+shift+b选择catkin_make build编译
    当出现[100%]Build target demo_imu_behavior时记为编译成功



**运行Node节点**

* ctrl + alt +t 打开终端
* 启动ROS系统核心：**在终端输入指令roscore**
* （如果没有写入）把工作空间的环境参数加载到终端：**source ~/catkin_ws/devel/setup.bash**
* 运行节点：**新建终端窗口，输入指令rosrun <包名> <节点名>**
  rosrun ssr_pkg chao_node

为了方便，不用每次运行ros都重新加载工作空间的环境参数，将source工作空间环境配置指令写入终端程序初始化脚本程序.bashrc

```
gedit ~/.bashrc

#滑到脚本文件最下面，添加：
source ~/catkin_ws/devel/setup.bash

（在source /opt/ros/noetic/setup.bash下方）

#者用vs code打开编辑

code ~/.bashrc
#滑到脚本文件最下面，添加：
source ~/catkin_ws/devel/setup.bash
```



**Node节点的完善**

此时的节点并不会和ROS其他节点产生交互，需要对其进行初始化操作

```
ros::init(argc,argv,"chao_node");
# 初始化操作，放在main函数第一行
# 这样就是一个完整的node节点了
```

还需要导入ros::init()函数所的库文件，此时：

* 打开CmaKelist.txt文件
* 找到Build这一节下的Specify liberaries to link(详细描述要连接的库)
* 把后面单注释的demo，放在最后一行，把项目名称改为节点名其他不变，保存，编译



对于ros中的while循环，如果想让他一直运行，评述都是讲条件设置为True,但是这样程序运行不受外部控制，ctrl+c也无法中止程序，所以在ros中，通常写为while(ros::ok()):{#code#},这样ctrl+c可以中断程序



### Topic话题和Mesage信息

ROS是分布式模块化的，会将一个完整的机器人任务分成多个节点去完成，这些节点通过Topic和Mesage完成交互
![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\屏幕截图 2025-01-25 172130.png)

**一个节点发布数据（Publisher发布者）到某个话题上，另一个节点通过订阅（Sbusciber订阅者）该话题拿到发布的数据**，话题通信也可以1v1,1vn,nv1,nvn的形式。**话题中的数据就是信息Mesage**。

消息有很多类型，ROS中消息类型在std_msgs头文件中有定义。

**查看消息类型**：ROS index网站上有（以后查ROS软件包等各种资源时，可以用这个网站去查相关信息）
index.ros.org
搜索std_msgs,点击website,即可查看信息类型有哪些



**发布者Publisher代码实现**：

* 确定话题名称和队友的消息类型

* 引入ROS消息类型对应的头文件std_msgs/String.h(消息的类型)

  ```
  #inculude <std_msgs/String.h>
  ```

* 初始化完成后定义ROS的NodeHandle对象，这是节点与ROS通讯的关键（可以理解为ROS是管家NodeHandle管理的豪宅，很多事情需要管家取打理这所豪宅）

  ```
  ros::NodeHandle nh;
  # NodeHandle对象名称为nh
  ```

* 由大管家NodeHandle发布一个话题并得到发布者Publisher

  ```
  ros::Publisher pub = nh.advertise<std_msgs::String>("topic",10);
  # 吩咐管家去生成一个Publisher，生成方法是管家的功能advertise,尖括号里定义这个发布者要发布的消息类型是什么，括号里第一个参数是话题名称（英文），第二个是消息缓存长度
  # 消息缓存长度：发布者发布消息，订阅者接收和处理消息，但是有可能老消息没处理完新消息又来了，这时候新的消息会按顺序排队等待倍订阅者处理，如果缓存队伍排满了，最先到达的消息则会被排挤掉，留出位置给新的消息
  ```

  

* 在while循环里发布消息

  ```
  # 生成要发送的消息包
  std_msgs::String msg;
  # 定义发布的消息数据
  msg.data = "发送消息";
  # 调用发布者的Publish()函数，把消息包传给发布者，发布消息到话题中
  pub.publish(msg);
  ```

* 运行新节点

  ```
  terminate1:
  roscore
  terminate2:
  rosrun ssr_pkg chao_node
  ```

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\屏幕截图 2025-01-26 162510.png)



* 打开新的终端窗口**查看活跃的话题rostopic list**

![](C:\Users\HP\Desktop\ROS\img\rostopic_list.png)



**话题中常用的工具**

* **查看话题中消息rostopic echo <话题名称>**
  如果消息是中文的，显示出来的是对应的Unicode字符编码，复制对应的编码，使用**echo -e < Unicode >**即可查看对应消息的内容
* **查看话题中发送消息的频率：rostopic hz < topic name >**
  average rate : num ——>表示1s内发送了num条消息
* **控制每秒发送消息的个数ros::Rate rate_name(num)**
  rate_name可以随便起，num表示发送消息的速度（/s）
  然后在while循环中调用**rate_name.sleep()**,会起到一个短暂的阻塞



### Subcriber订阅者节点

* 创建订阅者
  **ros::Subscriber sub = nh.subscribe("subscribe_topic_name",缓存长度，回调函数)；**
  回调函数名称可以随便取，需要在main函数前定义该回调函数

  ```
  # 每当一个消息到达订阅者处，ros系统就会在后台调用该回调函数，不需要我们手动去调用，我们只需要在函数里定义对该消息的处理方法即可
  
  void chao_callback(std_msgs::String msg)
  {
  	printf(msg.data.c_str());
  	printf("\n");
  }
  # printf函数的参数是char*指针字符数组但是我们的参数类型是string，所以需要先转换一下
  ```

  **c_str()**：将CPP中的string类型转为char*,因为printf是C语言中的函数，C语言没有string类型的数据
  
  
  
* 在循环函数中调用**ros::spinOnce();**
  相当于转过身取看一眼：当该节点正在忙于自己的事情时，调用到该spinOnce函数，转过身来看看有没有新的消息来到。所以如果没有调用该函数，这个节点就会在while函数里一直忙于自己的事情，不会处理新消息

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\chao_node.png)

* 最后在终端中先运行chao_node，在运行ma_node，这样两个节点之间的通讯就建立好了

* 调整与优化：使用**ROS_INFO()**函数可以显示接收到信息的时间
  如果信息是中文的，会显示乱码，所以要显示出中文消息，还要再main函数中**调用setlocale(LC_ALL,"");函数**如果ubuntu版本是中文的，直接“”，如果时英文版本“zh_CN.UTF-8”

  ```
  void chao_callback(std_msgs::String msg)
  {
  	ROS_INFO(msg.data.c_str());
  }
  ```

  ![](C:\Users\HP\Desktop\ROS\img\ma_node.png)

* 与第二个节点建立联系
  ！新创建的订阅者名称要不一样！

  为了更好的区别，接受到的消息使用ROS_WARN()函数来接收，此时打印的信息时黄色的
  ![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\屏幕截图 2025-01-28 121715.png)

* 节点订阅两个话题：

  ```c++
  #include <ros/ros.h>
  #include <std_msgs/String.h>
  
  # chao_node's topic is topic_chao
  # yao_node's topic is topic_yao
  
  void chao_callback(std_msgs::String msg)
  {
  	ROS_INFO(msg.data.c_str());
  }
  void yao_callback(std_msgs::String msg)
  {
  	ROS_WARN(msg.data.c_str());
  }
  
  int main(int argc,char* argv)
  {
      setlocale(LC_ALL,"");
      ros::init();
      ros::NodeHandle nh;
      ros::Subscriber sub_1 = nh.subscribe("topic_chao",10,chao_callback);
      ros::Subscriber sub_2 = nh.subscribe("topic_yao",10,chao_callback);
      
      while(ros::ok())
      {
          ros::spinOnce();
      }
      return 0;
  }
  ```



在一个复杂的机器人任务当中，存在复杂的话题订阅关系，可以通过**终端输入rqt_graph命令查看关系图**
![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\屏幕截图 2025-01-28 122511.png)





### launch运行多个节点

launch文件使用XML语法，批量启动节点是他的功能之一。

* **使用roslaunch就可以一次启动多个文件**，**格式：roslaunch <所在的软件包名> <launch文件名>**
  使用rosluanch打开launch文件后，会自动启动roscore

* **launch文件放在哪个软件包都可以，哪怕时一个文件的子目录都可以，启动launch文件之后会自动搜索对应节点的软件包目录**

* **launch文件的后缀：.launch**

```
launch 文件格式

<launch>

<node pkg="..." type=" " name=" "/>
<node pkg="..." type=" " name=" "/>
......

</launch>

# pkg = "包名称"
# type= "节点文件名称"
# name = "节点名称"
<launch>

<node pkg="ssr_pkg" type="chao_node" name="chao_node"/>
<node pkg="ssr_pkg" type="yao_node" name="yao_node"/>
<node pkg="art_pkg" type="ma_node" name="ma_node" output="screen"/>

</launch>

```

* 启动launch文件，接收到的消息仅显示由ROS_WARN展现的信息，对于ROS_INFO的信息则不会显示在屏幕上，如果需要展示ROS_INFO的信息，需要对订阅者的属性描述中加上output="screen"
  ROS_WARN无视该属性暴力输出
* 指定output="screen"后，订阅的所有话题信息都会展现在同一个终端窗口，不好对特定节点进行信息展示与调试。我们可以让某个节点单独运行在一个终端窗口，**在launch文件中添加属性launch-prefix="gnome-terminal -e"**



### Launch文件

标签总览：

* < launch > ....< /launch>：根标签
* < node>：启动节点
* < include>：嵌套（用这个launch打开另一个launch文件）
* < remap>：重命名（对话题的重命名）
* < param>：全局参数
* < rosparam>：加载参数
* < group>：节点分组
* < arg>：局部参数
* < machine>：远程标签
* < env>：环境变量
* < test>：测试节点



**< node>**属性

* pkg：节点所在的包名
* type：节点名称
* name：重定义节点名称
* args：传递参数
* output：日志输出



### python C++函数对比

| 函数   | Python                                                       | C++                                                          |
| ------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 订阅者 | sub = rospy.Subscriber("订阅话题名称"，消息类型，回调函数，queue_size = 缓存长度) | ros::Subscriber sub  = nh.subscribe("话题",回调函数，缓存长度); |
| 发布者 | pub = rospy.Publisher("“发布话题名称"，消息类型，queue_size = 缓存长度) | ros::Publisher pub = nh.advertise<消息类型>("话题名称"，缓存长度)； |
| 初始化 | rospy.init_node("节点名称")                                  | ros::init(argc,argv,"'节点名称')；                           |



### Python实现

**Python发布者实现**：

创建存放python程序编写的节点软件包：

* 创建软件包
  依赖项：rospy std_msgs

  ```
  cd ~/catkin_ws/src
  catkin_create_pkg ssr_py_pkg rospy std_msg
  ```

* 返回上一级目录，执行catkin_make编译
  这里的编译并不是编译ros节点，使用py编写的节点程序是不需要编译就可以直接运行的，在这里编译展示为了这个新建的软件包能够进入ROS的软件包列表，以便后续运行节点的的时候ROS能够在软件包列表中找到这个新建的软件包

* 在软件包中新建节点
  vscode打开软件包，src用于存放c++节点，需要新建一个文件夹scripts存放python

* 编写python节点

  ```
  #第一行指定Python的解释器
  #!/usr/bin/env python3
  
  # 指定运行环境的编码utf-8(如果不指定中文无法正常显示)
  #coding=utf-8
  ```
  
  
  
  **C++发布者节点**：
  
  * 召唤大管家**NodeHandle**
  * 向大管家申请初始化节点
  * 告诉ROS大管家需要发布的话题名称并索要能够发送消息的对象Publisher
  * 开启一个while循环，不停的使用Publisher发布消息
  
  
  
  python发布者节点也一样只是大管家变成了**rospy**
  
  ```
  #!/usr/bin/env python3
  #coding=utf-8
  
  import rospy
  from std_msgs.msg import String
  
  #Python主函数
  if __name__ == "__main__":
  	# 节点初始化，rospy中的init_node函数，参数为节点名称
  	rospy.init_node("chao_node")
  	# 登场台词
  	rospy.logwarn("chao_node 的python实现")
  	
  	# 告诉大管家要发布的话题名称并索要发布对象
  	pub rospy.Publisher("topic_chao",String,queue_size=10)
  	
  	# 发送消息频率控制对象
  	rate = rospy.Rate(10)
  	
  	while not rospy.is_shutdown():
  		rospy.loginfo("我要开始刷屏了")
  		msg = String()
  		msg.data = "i'm chao"
  		pub.publish(msg)
  		rate.sleep()
  	
  ```
  
  ubuntu中新建的文件通常出于安全考虑，不带有执行权限。我们需要给他执行权限
  
  * 打开节点程序所在文件夹
  
  * 右键在终端中打开（终端当前目录时该节点文件所在的位置）
  
  * 输入指令**chmod +x  节点名称**(加上.py后缀)：change mode eXecute修改权限
  
    chmod +x chao_node.py
  
  这样就可以在终端运行该节点了。



**Python订阅者节点实现**：

**C++订阅者实现**

* ROS大管家NodeHandle
* 初始化
* 构建一个回调函数，用于处理话题中接收到的消息包数据
* 告诉大管家NodeHandle需要订阅的话题名称，并设置消息包的回调函数
* 调用ROS的spinOnce函数查看消息

python的相同，大管家变为rospy,查看消息的函数spin()

```
#!/usr/bin/env python3
#coding=utf-8

import rospy
from std_msgs.msg import String

# 回调函数
def chao_callback(msg)：
	rospy.loginfo(msg.data)
	
#Python主函数
if __name__ == "__main__":
	rospy.init_node("ma_node")
	sub = rospy.Subscriber("topic_chao",String,chao_callback,queue_size=10)
	rospy.spin()
	
```

**！！！订阅者和发布者的queue_size不能少！！，要写queue_size=10这样的，不然不对（）**



## 机器人的运动控制

机器人运动

* 矢量运动
  * x轴（前后运动）
  * y轴（左右运动）
  * z轴（上下运动）

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\屏幕截图 2025-01-31 174431.png)

* 旋转运动
  * x轴（左右倾倒）
    大拇指指向x轴正方向，四指方向为左右倾倒的正方向
    ![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\屏幕截图 2025-01-31 174739.png)
  
  * y轴（俯仰，前倾后仰）
    大拇指指向y轴正方向，四指方向为俯仰的正方向
  
  * z轴（左右旋转）
  
    大拇指指向z轴正方向，四指方向为左右旋转的正方向

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\屏幕截图 2025-01-31 175025.png)



**矢量方向的量纲：米每秒	旋转运动的量纲：弧度每秒，机器人运动由各个适量和旋转方向的矢量叠加**



可以使用机器人控制的软件包**geometry_msgs**，进入ROS index网站搜索geometry_msgs，进入他的网站website，可以看到他的消息有很多类型，速度控制的消息包时Twist
![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\Twist.png)

包含了两个成员linear和angular分别是线性和有角度，类型都是vector3,
vector3这种类型包含三个成员，都是float64类型的，分别x,y,z



发布者发布话题/cmd_vel，创建一个速度消息包，给这个消息包成员赋值后把消息发布到话题中，机器人核心节点中控制速度的订阅了/cmd_vel话题，这样就实现了对机器人速度的赋值控制



### C++方法实现

* 创建一个速度控制的软件包，名为vel_pkg
  依赖项：rospy roscpp geometry_msgs

* 在软件包中创建vel_node.cpp
  **机器人速度控制节点公认的订阅话题为/cmd_vel**

  ```c++
  #include <ros/ros.h>
  #include <geometry_msgs/Twist.h>
  
  int main()
  {
  	#初始化
  	ros::init(argc,argv,"vel_node");
  	
  	#获取大管家，并获得发布者
  	ros::NodeHandle nh;
  	ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
  	
  	# 消息发布频率控制
  	ros::Rate rate(10);
  	
  	#创建消息包
  	geometry_msgs::Twist msg;
  	msg.linear.x = 0.1;
  	msg.linear.y = 0;
  	msg.linear.z = 0;
  	msg.angular.x = 0;
  	msg.angular.y = 0;
  	msg.angular.z = 0;
  	
  	#循环中发送消息
  	while(ros::ok)
  	{
  		pub.publish(msg);
  		rate.sleep();
  	}
  	return 0;
  }
  ```

* 在终端中运行wpr_simulation的仿真程序

  ```
  roslaunch wpr_simulation wpb_simple.launch
  ```

* ctrl shift o分屏，运行编写好的节点vel_node

  ```
  rosrun vel_pkg vel_node
  ```



### Python方法实现

思路一样，不同的只是.py不需要编译，但是软件包创建好之后要退回到catkin_ws目录执行catkin_make编译，把建好的软件包加载到ROS中，而且scripts文件夹中的vel_node.py需要添加可执行权限
在vel_node.py所在文件夹位置打开终端，执行命令chmod +x vel_node.py

```python
#!/usr/bin/env python3
#conding = utf-8

import rospy
from geometry_msgs.msg import Twist

if __name__ == "__main__":
	# 初始化
	rospy.init_node("vel_node")
	# 获取发布者
	pub = rospy.Publisher("/cmd_vel",Twist,queue_size=10)
	# 消息控制
	rate = rospy.Rate(10)
	# 消息包
	vel_msg = Twist()
	vel_msg.linear.x = 0.1
	
	# 消息发布
	while not rospy.is_shutdown():
		pub.publish(vel_msg)
		rate.sleep()
```





## 激光雷达测距

**作用**：用来探测周围障碍物的分布情况

**原理**：雷达工作的时候，会从发射器发射一道红外激光，光束集中障碍物后反射回来，由雷达的反射器接收，通过计时器计算发射光束和接收的时间间隔来计算障碍物与机器人的距离（时长 * 光速）/ 2；测完一个障碍物之后会旋转一定角度继续测量

**使用rviz观察机器人获取到的数据信息**（数据的可视化操作）

* 打开wpr_simulation wpb_simple.launch仿真机器人
* 新建终端，输入rviz打开
* Fixed Frame修改为base_footprint
* add添加rviz可以显示出的数据，添加RobotModel（机器人模型）和LaserScan(雷达)
* 修改LaserScan的Topic属性为/scan,size修改为0.03
  ![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\rviz.png)



### 激光雷达消息包格式

* ROS index搜索sensor_msgs
* 打开noetic版本的sensor_msgs，然后website,点击消息包LaserScan
* 查看激光雷达消息包的格式定义

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\激光雷达消息包格式.png)

最重要的数据是float32[] ranges，是一个array数组，每个数据都是float32类型，长度为360

数组中数据的排序与雷达扫描顺序是相同的，默认下是从-180到180的正向旋转，360长度，相当于每次测距旋转角度为1度。并不是每个测距都是有效的，有些测距超出有效测距范围，数值编程INF，也就是无穷大



**激光雷达扫描后的信息会通过激光雷达节点发布信息到/scan话题上，通过订阅该话题即可获得扫描到的测距信息**

### C++实现

**激光雷达的公认话题/scan**

```c++
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

void sensor_callback(sensor_msgs::LaserScan msg)
{
	# 获取正前方的测距信息
	float fMidDist = msg.ranges[180];
	ROS_INFO("前方测距：%f米",fMidDist);
}

int main(int arcv,char * argc[])
{
	# 正确显示中文信息
	setlocale(LC_ALL,"");
	#初始化
	ros::init("sensor_node");
	#订阅信息
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("/scan"，10，sensor_callback);
	# 一直查看信息
	ros::spin();
	
	return 0;

}
```



### Python实现

```python
#!/usr/bin/env python3
#conding = utf-8

import rospy
from sensor_msgs.msg import LaserScan

def sensor_callback(msg):
	dist = msg.ranges[180]
	rospy.loginfo("前方测距：%f米",dist)
	
if __name__ == "__main__"：
	rospy.init_node("sensor_node")
	
	sub = rospy.Subscriber("/scan",LaserScan,sensor_callback,queue_size=10)
	rospy.spin()
```





## 激光雷达避障

在ladir_behavior节点中，需要订阅激光雷达测距话题/scan，获取机器人前方障碍物距离信息，同时发布速冻控制的话题，根据障碍物信息完成实时控制机器人速度。

* 创建ladir_behavior_pkg软件包，同时退回上一目录catkin_make编译
  软件包包含依赖项：rospy roscpp sensor_msgs  geometry_msgs

### C++实现

```c++
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

# 发布速度控制话题(作为全局变量，这样可以在回调函数中调用该发布者取发布话题)
ros::Publisher vel_pub;

# 每次旋转的时间（如果不设置，每次旋转时间只有每次扫描的间隔时间，不足以避障）
int ncount = 0;	

# 每扫描一周调用一次该回调函数
void LaserScanCallBack(sensor_msgs::LaserScan msg)
{
	# 获取前方障碍物距离信息
	float fdist = msg.ranges[180];
	# 速度控制信息包
	geometry_msgs::Twist vel_msgs;
	
	if(ncount > 0)
	{
		ncount--;
		return;
	}
	
	# 避障
	if(fdist < 1.5)
	{
		# 向左旋转(弧度每秒)
		vel_msgs.angular.z = 0.5;
		# 旋转时间5s
		time = 50;
	}
	else
	{
		vel_msgs.linear.x = 0.1;
	}
	
	# 发布者将消息发布到话题上
	vel_pub.publish(vel_msg);
}

int main(int arcv,char * argc[])
{
	#初始化
	ros::init(argc,argv,"ladir_behavior_node");
	# 订阅激光雷达测距话题
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("/scan",10,LaserScanCallBack);
	# 定义发布者						
	vel_pub =  = nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
	
	ros::spin();
	
}

```

### Python实现

```python
#!/usr/bin/env python3
#conding = utf-8

import rospy
from sensor_msgs.msg import LaserScan
from geometry_msg.msg import Twist

# 旋转时间
count = 0;

# 回调函数
def LaserScanCallBack(msg):
    global vel_pub
    global count 
    # 获取前方障碍距离信息
    float fdist = msg.ranges[180]
    rospy.loginfo("前方障碍距离：%f米",fdist)
    # 速度控制消息包
    vel_msg = Twist()
    
    if count > 0:
        count-=1
        return
    
    if fdist < 1.5:
        count = 50
        vel_msg.angular.z = 0.3
    else:
        vel_msg.linear.x = 0.5
    
    # 发布速度消息
    vel_pub.publish(vel_msg)

if __name__ == "__main__":
    # 初始化
    rospy.init_node("ladir_behavior_node")
    
    # 订阅者
    ladir_sub = rospy.Subscriber("/scan",LaserScan,LaserScanCallBack,queue_size = 10)
    
    # 发布者
    vel_pub = rospy.Publisher("/cmd_vel",queue_size = 10)
```



## ROS消息包

之前涉及到的：

标准消息包：std_msgs

几何消息包：geometry_msgs

传感器消息包：sensor_msgs

### ROS消息包

* std_msgs标准消息包
* common_msgs常规消息包
  * sensor_msgs传感器消息包
  * geometry_msgs几何消息包
  * nav_msgs导航消息包
  * actionlib_msgs行为消息包
  * diagnostic_msgs自我诊断消息包
  * trajectory_msgs运动轨迹消息包（机械臂）



**进入ROS Index网站（index.ros.org/search）输入对应消息包名称，进入websize可以查看该消息包中包含的消息类型，点击消息类型可以查看该消息类型中的成员**

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\std_msgs.png)

* **Empty空类型，不传输消息，只是用来当作信号**
* **数组类型的数组长度是可以改变的**



![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\geometry_msgs.png)

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\sensor_msgs.png)

### 自定义消息包

**自定义消息包所需要的依赖项：rospy roscpp message_generation message_runtime**

* 创建消息包

  ```
  catkin_create_pkg qq_msgs rospy roscpp message_generation message_runtime
  ```

  可以看出，消息包的创建和软件包是一样的，是一种特殊的消息包

* 新建文件夹msg

* 在消息包中的msg文件夹创建文件，以.msg为后缀

* 定义新的消息类型：数据类型 变量名称

  ```
  string grate
  int64 star
  string data
  ```

* 添加编译规则

  * 打开Cmakelist.txt文件，确保find_package里面填入了message_genaration和message_runtime

  * 往下翻，找到add_messgae_files这一句，ctrl+/取消注释

  * 把里面的.msg文件删掉，填上自定义消息包的文件名称（加上后缀

  * 继续往下，找到generate_messages这一节，ctrl+/取消注释，这一节表明新的消息类型所需要依赖的其他消息包列表（这里只用到了std_msgs中的string,int64，所以只需要写std_msgs）

  * 继续往下，找到catkin_package这一节，选择CATKIN_DEPENDS这一行，取消注释，并确定messgae_runtime在其中。这一句是为了依赖了这个新消息包的其他软件包能够在运行的时候使用这个新定义的消息类型

  * 打开package.xml，往下翻到依赖项列表，确保build_depend和exec_depend都列出了message_genaration和message_runtime，如果缺失就补全

    这里缺少了，要补全
    ![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\自定义消息包packa.xml.png)



* 消息包编译：~/catkin_ws执行catkin_make

* 查看消息包是否进入ROS消息包列表：rosmsg show 消息包名称/消息类型名称

  ```
  rosmsg show qq_msgs/Carry
  ```

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\自定义消息包流程.png)



### C++使用自定义消息包

* 引入新消息类型的头文件

  ```
  #include <qq_msgs/Carry.h>
  ```

* 在编译规则中添加消息包的依赖（**告诉编译器一定要编译新消息包，否则会报错，找不到对应消息类型**）

  * 如果该软件包在创建时以及包含了新消息类型的软件包，就和其他消息包一样正常使用

  * 如果软件包在创建时没有包含新消息包依赖项，则需要手动添加（一定要掌握）

    * 打开软件包的Cmakelist,找到find_package一节，把自定义新消息包添加上去

    * 来到文件末尾，添加add_dependencies(节点名称 新消息包名称_generate_messages_cpp)

      ```
      add_dependencies(sub_node qq_msgs_generate_message_cpp)
      ```

    * 打开package.xml，将新消息包添加到build_depend和exec_depend中

    * 然后进入~/catkin_ws工作空间入口执行编译操作catkin_make

  

### Python使用自定义消息包

* 引入新消息类型的头文件

  ```
  from qq_msgs.msg import Carry
  ```

* 在编译规则中添加消息包的依赖

  * 如果该软件包在创建时以及包含了新消息类型的软件包，就和其他消息包一样正常使用
  * 如果软件包在创建时没有包含新消息包依赖项，则需要手动添加（一定要掌握）
    * 打开软件包的Cmakelist,找到find_package一节，把自定义新消息包添加上去
    * 打开package.xml，将新消息包添加到build_depend和exec_depend中
    * 然后进入~/catkin_ws工作空间入口执行编译操作catkin_make





## ROS栅格地图

机器人导航所需要的地图数据就是ROS导航软件包里的map_server节点在话题/map中发布的数据，消息类型是nav_msgs消息包中的OccupancyGrid(占据栅格)，就是一直正方形小格子组成的地图，每个格子填入一个数字表示障碍物占据的情况（0表示没有障碍物，-1表示未知）

栅格可以自定义划分，栅格越小划分越精细，越接近于障碍物的轮廓，但是对于一个地图来说，栅格越小栅格数量越多，地图的数据量也就越多，处理更麻烦。

栅格的尺寸：栅格的边长，也用于体现地图分辨率

ROS栅格地图格式

* ROS Index中查找map_server节点

* 找到map_server节点下的Published Topics子目录

* 可以看到map这个话题，消息类型是nav_msgs/OccupancyGrid

* 点击进去查看这个消息类型的数据结构
  有三个成员，第二个是地图的参数信息，第三个是一个int8八位整形的数组

  数组排列方式：从(0,0)开始，也就是地图的左下角，取值范围0~100

  **地图参数信息INFO：**
  ![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\地图参数信息.png)

* map_msgs
  * header
    * frame_id    地图名称
    * stamp  时间戳（设置为当前时间ros::Time::now()）
  * info
    * map_load_time  地图加载时间
    * resolution   地图分辨率
    * width    地图宽度
    * height    地图高度
    * origin    与地图坐标系原点的偏移量
      * position.x
      * position.y
  * int8 data[]    地图栅格数据（在确定好地图大小后，要先把数组大小确定下来）
    * C++：msg.data.resize(width*height)
    * PY：msg.data = [0] * width *  height





### C++实现

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\栅格地图实现流程.png)

```c++
#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>

int main(int argc, char *argv[])
{
    
    ros::init(argc,argv,"map_pub_node");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<nav_msgs::OccupancyGrid>("/map",10);
    
    ros::Rate rate(1);

    // 获取地图消息包
    nav_msgs::OccupancyGrid msg;
    // 赋值
    // 地图名称
	msg.header.frame_id = "map";
    // 时间戳设置为当前时间
    msg.header.stamp = ros::Time::now();

    msg.info.origin.position.x = 0;
    msg.info.origin.position.y = 0;
    // 地图分辨率（米每栅格）
    msg.info.resolution = 1.0;
    // 地图大小
    msg.info.width = 4;
    msg.info.height = 2;

    //调整数组大小宽度*高度
    msg.data.resize(4*2);
    msg.data[0] = 100;
    msg.data[1] = 100;
    msg.data[2] = 0;
    msg.data[3] = -1;

    while(ros::ok())
    {
        pub.publish(msg);
        rate.sleep();

    }
    
    return 0;
}

```

* 运行该节点
* ctrl shift o分频，在终端输入rviz可视化该地图
  * riviz中添加add坐标轴Axes
  * 添加Map地图显示，map订阅话题是/map就可以可视化栅格地图了

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\rviz可视化栅格地图.png)



### python实现

```python
#!/usr/bin/env python3
#conding=utf-8

import rospy
from nav_msgs.msg import OccupancyGrid

if __name__ == "__main__":
    rospy.init_node("map_pub_node")
    rate = rospy.Rate(10)

    # 获取发布者
    pub = rospy.Publisher("/map",OccupancyGrid,queue_size=10)
    # 定义地图消息包
    msg = OccupancyGrid()
    msg.header.frame_id = "map"
    msg.header.stamp = rospy.Time.now()
    # 地图起点与坐标轴偏移量
    msg.info.origin.position.x = 0
    msg.info.origin.position.y = 0
    # 地图分辨率
    msg.info.resolution = 1.0
    # 地图大小
    msg.info.width = 4
    msg.info.height = 2
    # 栅格赋值
    msg.data = [0]*4*2
    msg.data[0] = 100
    msg.data[1] = 100
    msg.data[2] = 0
    msg.data[3] = -1

    # 消息发布
    while not rospy.is_shutdown():
        pub.publish(msg)
        rate.sleep()
```





## SLAM

栅格地图是通过SLAM生成的

**Simultaneous Localization And Mapping:同时定位与地图创建**

* 定位：机器人知道自己在地图中的哪个位置
* 地图创建

**激光雷达SLAM定位方法：障碍物点云（激光雷达扫描到的障碍物信息与上一次扫描到的障碍物信息进行特征相同点的匹配，拼接更新实时地图信息）**

原理：SLAM通过激光雷达扫描障碍物，实时获取障碍物信息后通过RViz将检测到的地图信息可视化

**机器人一边前行一边通过激光雷达扫描障碍物信息，同时将障碍物信息发给SLAM后实时构建地图信息，与此同时通过RViz实现可视化操作。**

**涉及内容：机器人运动控制，激光雷达扫描障碍物，雷达避障，SLAM,RViz可视化地图**

* 激光雷达扫描障碍物，通过激光雷达节点发布/scan话题将消息发布
* SLAM节点订阅/scan话题获取地图信息，构建地图，创建话题/map发布地图信息
* RViz订阅/map话题，实现地图的可视化

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\SLAM.png)



ROS中提供了很多现成的SLAM软件包（功能包），先介绍第一款Hector_Mapping



### Hector_Mapping

通过ROS index网站查找Hector_Mapping功能包信息

* 订阅的话题

  * **/scan（sensor_msgs/LaserScan）**
  * /systemcommand（不常用）

* 发布的话题

  * 建图相关
    * /map(nav_msgs/OccupancyGrid)发布地图信息

  * 定位相关
    * /slam_out_pose(geometry_msgs/PoseSlamped)
    * /poseupdate(geometry_msgs/PoseWithConvarianceSlamped)



### 实现步骤

* 安装Hector_Mapping功能包
  在终端中输入sudo apt install ros-noetic-hactor-mapping

* 下载wpr_simulation功能包（之前装过的步骤）

* 运行机器人仿真环境
  此时机器人核心节点运行起来了，其激光雷达也开始工作了，并发布了/scan话题将信息发布出去（此时需要该数据的节点可以订阅该话题即可获得扫描的信息）

  ```
  roslaunch wpr_simulation wpb_stage_slam.launch
  ```

* 运行SLAM功能包hector_mapping
  hector_mapping功能包的包名和节点名称都是hactor_mapping
  运行起来后，该节点订阅了/scan话题，获取到了扫描的信息，同时发布话题/map构建了地图，将信息发布到/map话题中

  ```
  rosrun hector_mapping hactor_mapping
  ```

* 运行Rviz可视化

  ```
  rorun rviz rviz
  ```

  * 添加RobotModel
  * 添加LaserScan,选择Topic：/scan，选择大小为0.03
  * 添加Map，选择话题Topic：/map

* 运行机器人速度控制工具，控制机器人的运动状态

  ```
  rorun rqt_robot_steering rqt_robot_steering
  ```

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\hactor_mapping.png)



### 使用launch文件实现

按步骤，需要运行wpb_stage_slam.launch文件，但是之前运行的都是单个节点，此时是一个launch文件，可以参考C语言引入其他头文件的写法，是通过#include引入的，在launch文件中也是

**launch文件中引入其他launch文件的，是使用标签名称为include的**

```
<include file = "launch文件的具体路径" />

launch文件的具体路径可以使用rospack指令来获取软件包的完整路径：
指令语法：$(find 软件包名字) ——>这样相当于~/catkin_ws/src/对应的软件包
$(find wpr_simulation) ——>~/catkin_ws/src/wpr_simulation

但是这样之后还有跟上/launch/wpb_stage_slam.launch才是完整的launch文件路径

！！结束标记的/不能忘记：可以当作是包装盒打包完之后封装起来
```

剩下三个指令都是常规的节点指令,完整launch文件：

```
<launch>

    <include file="$(find wpr_simulation)/launch/wpb_stage_slam.launch" />
    <node pkg="hector_mapping" type="hector_mapping" name="hector_mapping"/>
    <node pkg="rviz" type="rviz" name="rviz" />
    <node pkg="rqt_robot_steering" type="rqt_robot_steering" name="rqt_robot_steering" />
 

</launch>
```

**运行launch文件前需要在工作空间执行编译操作，目的是为了让slam_pkg这个软件包进入ros功能包列表，否则后续运行launch文件时会提示找不到该文件**



**保存rviz配置文件**

* rviz界面中file-save config as
* 保存地址选择slam_pkg中新建的文件夹rviz当中，保证目录清晰
* 文件名slam.rviz

这样配置文件就保存好了，要是想运行当前slam这个rviz配置，终端中输入

```
rosrun rviz rviz -d /home/robot/catkin_ws/src/slam_pkg/rviz/slam.rviz
```

也可以改写launch文件，让他在启动rviz时就自动加载该配置

```
<node pkg="rviz" type="rviz" name="rviz" args="-d $(find slam_pkg)/rviz/slam.rviz"/>
```

```c++
<launch>

    <include file="$(find wpr_simulation)/launch/wpb_stage_slam.launch" />
    
    <node pkg="hector_mapping" type="hector_mapping" name="hector_mapping"/>
    
    <node pkg="rviz" type="rviz" name="rviz" args="-d $(find slam_pkg)/rviz/slam.rviz"/>
    
    <node pkg="rqt_robot_steering" type="rqt_robot_steering" name="rqt_robot_steering" />
 

</launch>
```



### Hector_Mapping参数设置

参数有很多，本次只使用这三个参数设置

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\hector_mapping参数.png)



现在对节点hector_mapping在launch文件中进行参数设置，在node大箱子装一个小箱子param,

```
<nodepkg= type=  ....> 
	....
</node>

只有一个箱子的末尾结束标识</node>可以简化:
<node pkg= type= ..../>

现在需要多加一个参数设置的小箱子，所以采用第一种标签方式
参数标签param，形式：
<param name="需要设置的参数名称" value=设置的参数值/>
```

```c++
<launch>

    <include file="$(find wpr_simulation)/launch/wpb_stage_slam.launch" />
    
    <node pkg="hector_mapping" type="hector_mapping" name="hector_mapping">
    	<param name="map_update_distance_thresh" value=0.1/>
    	<param name="map_updata_angle_thresh" value=0.1/>
    	<param name="map_pub_period" value=0.1/>
    </node>
    
    <node pkg="rviz" type="rviz" name="rviz" args="-d $(find slam_pkg)/rviz/slam.rviz"/>
    
    <node pkg="rqt_robot_steering" type="rqt_robot_steering" name="rqt_robot_steering" />
 

</launch>
```







## TF系统



### 定位信息描述

SLAM是实时定位与地图建构，前面已经知道了如何建构地图，那么定位则是通过TF获取



**定位信息的描述**：建立坐标系原点，机器人在运行过程中，我们需要知道机器人与地图坐标系原点的空间关系，为了方便描述这种关系，给机器人和地图原点各自定义了坐标系。地图原点坐标系起名为map，机器人坐标系的原点定在机器人底盘投影到地面的中心位置，起名为base_footprint。方向均遵循右手法则。
map坐标系作为父坐标系机器人坐标系作为子坐标系。

机器人相对于原点的空间关系可以用**子坐标系于父坐标系的x，y，z的偏移量**，
**对应地面移动机器人而言，z轴偏移量为0**

还有一组描述关系是**子坐标系在x，y，z轴上的角度偏差**（x轴上的角度偏差时子坐标系绕着x轴旋转后的角度偏差【可以用y轴来确定，绕x轴旋转一定角度，该角度大小等于子坐标系y轴与父坐标系y轴的偏移角】，其他同理）

**对于地面机器人，无法前后俯仰（y）和左右倾斜（x），所以在y轴和x轴的角度偏移为0**

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\机器人定位描述.png)





### TF获取定位信息描述

TransForm:坐标系变换

信息获取流程：

* TF发布节点发布话题/tf

* 其他节点订阅/tf话题来查询当前运行的节点网络中都存在哪些坐标系，已经与地图坐标系原点的空间关系

* 可以通过RViz可视化TF坐标系（只能看到图像）
  TF坐标系中有很多坐标系关系，可以在RViz中TF的Frames中只选择展示map,base_footprint两个坐标系，就可以查看这两个坐标系的位置了（Make Scale可以调整坐标系的大小显示）

* 查看具体数值：

  * 打开新终端，先查找关于TF的话题

    ```
    rostopic list
    ```

  * 可以看到/tf话题正在工作

  * 在终端查看消息具体数值：

    ```
    rostopic echo /tf
    ```

  * 找到父坐标系：map    子坐标系:base_footprint的就可以查看了

  

  

  

  

  **查看/tf话题的消息格式**

  ```
  rostopic type /tf
  tf2_msgs/TFMessage
  // rostopic type 话题名称   可以查看话题的消息格式
  ```

  * 进入ros index网站查看tf2_msgs中的TFMessage消息类型的结构
    geometry_msgs/TransformStamped类型的数组

  * 点击geometry_msgs/TransformStamped查看这个消息类型的结构

    * header：之前地图的时候也见到过，里面的frame_id是父坐标系名称

    * string child_frame_id：子坐标系的名称

    * tansform：里面是子坐标系与父坐标系的空间关系
      * translation:与x,y,z的偏移量
      * rotation：与x,y,z的角度偏移

  ![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\TF消息包.png)



**子坐标系很多，可以通过rqt_tf_tree查看各个坐标系间的关系**

```
rorun rqt_tf_tree rqt_tf_tree
```

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\TF_tree.png)







## 里程计

建图方式：hector_mapping 和gmapping

假设机器人正在一个两侧都是一模一样墙壁的距离很长的小道上前行，对于hector_mapping的建图方式是基于激光雷达扫描障碍的方式来建图的，在这样的小道上，激光雷达扫描出的障碍物信息一样，会认为机器人并没有移动，所以在RViz显示的地图信息中，机器人是停止运动了的，但是实际上机器人依然在前进。

但是如果使用gmapping方式建图，则不会出现这种情况，因为gmapping建图方式中使用里程计来计算机器人的运动情况。

视野里的特征不再变化，但是机器人还在运动，通过统计机器人轮子转动的圈数 * 周长就可以计算出机器人移动的距离。**这种统计电机转速计算机器人位移的方法就是激光雷达SLAM中常用的电机里程计。**

**里程计并不是硬件，而是软件算法，这个算法运行在机器人的驱动节点中。这个电机里程计算法得到的位移数据也是以TF消息包的形式发布到/tf话题的。**

里程计得到的TF坐标系是odom。激光雷达SLAM输出的是map到base_footprint的TF数据，里程计输出的是odom到base_footprint的TF。





## Gmapping

里程计计算机器人位移方法也会出现误差，例如机器人的轮子打滑等，就会出现偏差，如果不进行修正，累计下来会出现更严重的误差。由此使用里程计计算和障碍物点云两者相互配合修正，可以弥补hector_mapping和里程计计算的缺点。

### 核心算法：障碍物点云配准

**也就是先使用里程计计算位移，然后通过雷达点云贴合障碍物修正里程计误差**

**障碍物点云配准：**将激光雷达扫描到的点云移动到里程计计算出的机器人位置这个点上，如果点云与障碍物没有重合，说明里程计产生了误差。这时候直接将激光雷达的点云贴合到障碍物上同时机器人位置也会被拉过来，则只需要在里程计估算的位置上加上这一小段位移（里程计估算的位置与激光雷达扫描点云位置）就可以将点云与障碍物重合了

里程计输出的是odom到base_footprint的TF，激光雷达SLAM输出的是map到base_footprint的TF，由于base_footprint已经被里程计占用了，所以SLAM会谦让里程计，输出map到odom再到base_footprint的TF

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\gmapping的TF.png)



### SLAM两大算法区别

**Gmapping 与Hector_mapping**

* Gmapping：障碍物点云配准（里程计+障碍物点云）
* Hector_mapping：直接将障碍物点云贴合障碍物轮廓所得出的位移作为定位结果
  他的TF是从map到scanmatcher_frame

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\hector_mapping的TF.png)

但是如果想要在rviz上显示地图和机器人模型，就必须实现从map到base_footprint的TF，这样才能将机器人本身的TF与map连接起来形成完整的TF树。所以hectormapping还会另外输出一段map-odom-base_footprint的TF。但是这里和Gmapping输出的不一样，hectormappingshuchudemap-odom的TF目的不是为了修正里程计误差，而是让base_footprint的位置始终和scanmatcher_frame保持一致（就以上一个小道来说，为了抵消里程计的变化，odom会输出一个反向增长的odomTF）



### Gmapping的使用

查看gmapping软件包相关信息

* gmapping软件包的节点名称：slam_gmapping

* 订阅的话题
  * /tf
  * /scan
* 发布的话题
  * /map_metdata（地图相关的数据）
  * /map（栅格地图）
  * /~entropy

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\gmapping软件包信息.png)

slam_gmapping对TF的要求：

* 激光雷达节点的TF到base_link间的TF
  也就是激光雷达坐标系到底盘坐标系的TF（这里的雷达坐标系没有具体名称，所以还需要/scan话题中雷达数据的header里的frame_id保持一致）
* base_link到odom之间有连接
  也就是上一个的里程计的TF

![](C:\Users\HP\Desktop\smart_car\HNUsmartcar_2025_report\自动化2303_甘明珍\1月\ros\img\gmapping软件包tf需求.png)



**所以如果想要使用Gmapping建图，需要其他节点发布了/scan话题，同时需要TF树中激光雷达坐标系与地盘坐标系有TF连接，地盘坐标系与里程计odom有TF连接**

* 运行机器人仿真节点

  ```
  roslaunch wpr_simulation wpb_stage_robocup.launch
  ```

* 查看活跃的话题有无/scan

  ```
  rostopic list
  ```

* 查看激光雷达的header中的frame_id

  ```
  rostopic ehco /scan --noarr
  ```

* 确认需求的TF关系

  ```
  rosrun rqt_tf_tree rqt_tf_tree
  ```

* 都满足后运行slam_gmapping节点建图

  ```
  rosrun gmapping slam_gmapping
  ```

* 启动rviz可视化建图
  配置：

  * LaserScan：话题/scan
  * RobotModel
  * Map：话题/map

* 机器人运动控制（让机器人在仿真中都走一遍，把地图扫描出来）

  * 速度控制器

    ```
    rosrun rqt_robot_steering rqt_robot_steering
    ```

  * 键盘控制器

    ```
    rosrun wpr_simulation key_board_vel_ctrl
    ```



### 使用launch文件

同时加载yinbaocunhaoderviz配置参数

```c++
<launch>
    
    <include file="$(find wpr_simulation)/launch/wpb_stage_robocup.launch" />
    
    <node pkg="gmapping" type="slam_gmapping" name="slam_gmapping"/>
    
    <node pkg="rviz" type="rviz" name="rviz" args="-d $(find slam_pkg)/rviz/gmapping.rviz"/>
    
    <node pkg="wpr_simulation" type="keyboard_vel_ctrl" name="keyboard_vel_ctrl"/>


</launch>
```



### Gmapping参数设置

