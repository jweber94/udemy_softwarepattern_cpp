#include <iostream>
#include <type_traits>

// concept with traits class
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T>
T add(T a, T b) {
    return a + b;
}

// concept without traits class
template <typename T>
concept Printable = requires (T t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};

template <Printable T>
void print(const T& value) {
    std::cout << value << std::endl;
}

class MyClassPrintable {
    public:
        void foo(const std::string& bar) {
            std::cout << "foo " << bar << std::endl;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const MyClassPrintable& obj) {
            os << "MyClass overloaded << operator";
            return os;
        }
};

class MyClass {
    public:
        void foo(const std::string& bar) {
            std::cout << "foo " << bar << std::endl;
        }
};

int main() {
    double a = add<double>(4, 2);
    MyClass cl1;
    MyClassPrintable cl2;
    // print<MyClass>(cl1); // does not work because the concept condition is not fulfilled
    print<MyClassPrintable>(cl2);
    return 0;
}