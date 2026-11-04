#include <iostream>
#include <tuple>
#include <utility> // std::integer_sequence 所在的头文件

using namespace std;

// 2. 实际干活的辅助函数：利用参数包展开（...）和编译期索引
template <typename Tuple, size_t... Is>
void print_tuple_impl(const Tuple& t, std::index_sequence<Is...>) {
    // 这里利用了 C++17 的折叠表达式 (Fold Expression)
    // 编译器会将其展开为：(std::cout << std::get<0>(t) << " "), (std::cout << std::get<1>(t) << " ")...
    ((std::cout << std::get<Is>(t) << " "), ...);
    std::cout << std::endl;
}

// 1. 面向用户的接口函数
template <typename... Args>
void print_tuple(const std::tuple<Args...>& t) {
    // 动态获取 tuple 元素的数量：sizeof...(Args)
    // make_index_sequence 会自动生成 index_sequence<0, 1, 2, ...> 类型的对象实例传入
    print_tuple_impl(t, std::make_index_sequence<sizeof...(Args)>{});
}

int main() {
    auto my_tuple = std::make_tuple(42, 3.14, "Hello C++14");
    
    // 触发调用
    print_tuple(my_tuple); // 输出: 42 3.14 Hello C++14 

    std::make_index_sequence<5> seq; // 实例化为一个 index_sequence<0, 1, 2, 3, 4>
    std::integer_sequence<int, 1, 2, 3> seq2; // 实例化为一个 integer_sequence<int, 1, 2, 3>
    std::index_sequence_for<int, double, char> seq3; // 实例化为一个 index_sequence<0, 1, 2>
    
    return 0;
}
