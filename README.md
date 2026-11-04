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

# C++14（11 的小补集，增量升级，改动不大，很多中间过渡项目）
C++14 ≈ C++11 + 少量便利特性，没有颠覆性能力
## 高频新增：
- std::make_unique（超级常用！11 只有 make_shared，没有 make_unique）
- 泛型 lambda：auto f = [](auto x){return x+1;}
- lambda 里面可以用 auto 参数
- 变量模板
- std::integer_sequence（写模板元编程、序列化偶尔碰到）

# C++17
在 14 基础上，大量工程上非常舒服的特性，做机器人 / 边缘 AI 开发高频：
- 结构化绑定 auto [a,b] = func();（读 pair、map、结构体返回值，写 ROS 数据、解析结果巨爽）
- if constexpr（编译期分支，模板代码、跨平台 SDK、不同硬件适配必备，边缘开发经常用）
- std::optional<T>：可以表达“有没有值”，代替裸指针判断，ROS 服务返回、AI 推理结果（推理失败 / 成功）非常适合
- std::variant 类型联合体，替代丑陋的 union
- 内联变量 inline static（头文件放全局常量，ROS 消息定义、配置常量很常用）
- 折叠表达式（模板参数包，写通用序列化、工具函数）
- 类模板参数推导 CTAD：std::vector v{1,2,3} 不用写 vector<int>
- std::filesystem（文件路径、创建文件夹、读取模型文件！RKNN/TensorRT 加载模型必用）

