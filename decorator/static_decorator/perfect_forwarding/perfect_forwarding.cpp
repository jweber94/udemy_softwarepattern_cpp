#include <iostream>
#include <utility>

// Eine Funktion, die perfektes Weiterleiten verwendet
template <typename T>
void forwardFunction(T&& value) {
    std::cout << "Received value: " << value << std::endl;
}

template <typename T>
void stdForwardFunction(T&& value) {
    someOtherFunction(std::forward<T>(value));
}

void someOtherFunction(int& x) {
    std::cout << "Received l-value reference: " << x << std::endl;
}

void someOtherFunction(int&& x) {
    std::cout << "Received r-value reference: " << x << std::endl;
}

int main() {
    int x = 42;
    const int y = 17;

    // Hier rufen wir forwardFunction mit verschiedenen Parametern auf
    forwardFunction(x);  // x ist ein l-value
    forwardFunction(123);  // 123 ist ein r-value
    forwardFunction(y);  // y ist ein const l-value

    // std::forward
    stdForwardFunction(x);      // calls lvalue version of underlying someOtherFunction
    stdForwardFunction(124);    // calls rvalue version of underlying someOtherFunction
    return 0;
}
