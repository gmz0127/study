## 话题

* 创建发布者对象（向ROS Master注册话题信息）

  ```
  # python
  pub = rospy.Publisher(话题名称，消息类型，queue_size=缓存长度)
  ```

  ```
  // c++
  ros::Publisher pub = nh.advertise<消息类型>(话题名称，缓存长度)
  ```

* 发布者发布消息

  ```
  # python
  pub.publish(消息对象)
  ```

  ```
  // c++
  pub.publish(消息对象)
  ```

* 消息发布频率控制

  ```
  # python
  # 1.获取控制对象
  rate = rospy.Rate(频率)
  # 2.控制
  rate.sleep()
  ```

  ```
  // c++
  // 1.获取控制对象
  ros::Rate rate(频率)
  // 2.控制
  rate.sleep()
  ```

* 休眠

  ```
  # python
  rospy.sleep(时间/秒)
  ```

  ```
  // c++
  ros::Duration(时间/s).sleep()
  ```

* 获取订阅对象

  ```
  # python
  sub = rospy.Subscriber(话题，消息类型，回调函数，queue_size=缓存长度)
  ```

  ```
  // c++
  ros::Subscriber sub = nh.subscribe(话题，回调函数，缓存长度)
  ```

* 回调函数

  ```
  # python
  def callback_name(消息参数)：
  ```

  ```
  // c++
  void callback_name(const修饰的消息类型的引用)
  void callback(const std_msgs::String& msg)
  {}
  ```

  



## 服务

* 创建客户端

  ```
  # python
  # name:话题名称，server-class:服务信息类别
  client = rospy.ServiceProxy(name,server-class)
  ```
  
  ```
  // cpp
  ros::ServiceClient client = nh.serviceClient<服务消息载体类型>(话题名称);
  
  ros::ServiceClient client = nh.serviceClient<server_pkg::addint>("/addint");
  ```
  
  
  
* 创建服务端

  ```
   # python
   server = rospy.Service(话题名称,服务消息载体类型,回调函数)
  ```

  ```
  // cpp
  ros::NodeHandle nh;
  ros::ServiceServer server = nh.advertiseService(话题名称,回调函数);
  ```

  

* 创建响应对象

  ```
  # python
  response = addintResponse()
  ```

  ```
  // cpp
  // 通过获取服务对象调用响应和请求对象
  // 获取服务对象
  server_pkg::addint ai;
  // 通过服务对象调用请求则中的数据
  ai.request.num1 = 10;
  ```

  

* 客户端挂起等待服务端启动

  ```
  # python
  # 1.通过客户端对象等待
  client = rospy.ServiceProxy(name,server_class)
  client.wait_for_service()
  
  # 2.通过rospy等待
  rospy.wait_for_service(话题名称)
  ```

