#include <iostream>
#include <experimental/coroutine>

generator<int> fibonacciSequence(int n) {
    int a = 0, b = 1;
    co_yield a;
    co_yield b;

    for (int i = 2; i < n; ++i) {
        int next = a + b;
        co_yield next;
        a = b;
        b = next;
    }
}

int main() {
    int n = 10; // Anzahl der Fibonacci-Zahlen

    std::cout << "Fibonacci Sequence (" << n << " numbers):" << std::endl;

    auto sequence = fibonacciSequence(n);

    for (auto value : sequence) {
        std::cout << value << " ";
    }

    std::cout << std::endl;

    return 0;
}
