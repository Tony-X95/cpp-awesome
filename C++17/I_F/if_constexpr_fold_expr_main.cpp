#include <iostream>

template <typename... Args>
bool all_are_integrals(Args... args) {
    if constexpr (sizeof...(args) == 0) {
        return false; // Base case: no arguments, all are integrals
    } else {
        return (std::is_integral_v<Args> && ...); // Fold expression to check all types
    }
}

int main() {
    std::cout << std::boolalpha; // Print bools as true/false
    std::cout << "All are integrals (1, 2, 3): " << all_are_integrals(1, 2, 3) << "\n"; // true
    std::cout << "All are integrals (1, 2.5, 3): " << all_are_integrals(1, 2.5, 3) << "\n"; // false
    std::cout << "All are integrals (): " << all_are_integrals() << "\n"; // false (no arguments)
    return 0;
}