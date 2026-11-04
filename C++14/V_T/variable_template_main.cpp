#include <iostream>
#include <iomanip>

using namespace std;

// 1. 定义一个变量模板
template<typename T>
constexpr T pi = T(3.1415926535897932384626433832795L);

int main() {
    // 2. 根据不同的模板参数，直接生成并使用对应类型的变量
    float  pi_f  = pi<float>;       // 实例化为一个 float 变量
    double pi_d  = pi<double>;      // 实例化为一个 double 变量
    
    std::cout << std::setprecision(15);
    std::cout << "Float pi: " << pi_f << std::endl;  // 精度较低
    std::cout << "Double pi: " << pi_d << std::endl; // 精度较高

    return 0;
}
