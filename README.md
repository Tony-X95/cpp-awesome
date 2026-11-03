# cpp-awesome
A curated collection of awesome C++ resources, libraries, and tools.

# C++11
## new features
- auto 自动类型推导、范围 for（for(auto &x : vec)）
- 右值引用 &&、移动语义、std::move
- 智能指针：std::shared_ptr / std::unique_ptr（ROS2 rclcpp 到处都是！重中之重）
- lambda 表达式（[](int a){}）
- 初始化列表 {}、统一初始化
- nullptr（替代 NULL）
- 枚举 class enum（强类型枚举）
- std::thread、std::mutex、std::condition_variable（Linux 多线程，ROS 节点、回调线程必用）
- std::function、std::bind（ROS 回调函数底层大量依赖）
- 容器新增：unordered_map / unordered_set  
## ❌ C++11 限制：
- lambda 不能捕获 this 再移动、没有泛型 lambda
- 没有 std::make_unique
- 没有结构化绑定、if constexpr、inline 变量
- 没有 std::optional、std::variant、std::any