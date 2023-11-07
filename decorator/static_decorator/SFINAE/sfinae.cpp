#include <iostream>
#include <type_traits>

// overload of the add function for arithmetic datatypes
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
add(T a, T b) {
    return a + b;
}

// overload of the add function for non-arithmetic datatypes
template <typename T>
typename std::enable_if<!std::is_arithmetic<T>::value, T>::type
add(T a, T b) {
    std::cout << "This type does not support addition." << std::endl;
    return T{};
}

int main() {
    // usage of the arithmetic overload
    int result1 = add(2, 3); // the compiler generates the template arguments T implicitly by type deduction. This way, we do not need to tell the compiler explicitly which type he should use for the template argument (add<int>(2, 3);)
    std::cout << "Result 1: " << result1 << std::endl;

    // usage of the non-arithmetic overload
    std::string result2 = add("Hello, ", "World"); // also type deduction by the compiler
    std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}
