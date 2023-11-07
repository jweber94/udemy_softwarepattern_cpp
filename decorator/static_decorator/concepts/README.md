# Concepts
+ ***Concepts are an enhancement of the C++ template framework since C++11***

## Main Advantages
+ Enforcement of types, methods or members at compile time
+ Better compiler error messages, because the demanded types are more clear when it comes to templates
+ More descriptive code

## Implementation Details
+ Concepts can (but don't need to be) handed over to template argument definitions
    - CAUTION: `typename` in `template<typename T>` is *NOT* a concept! `typename` is a standart keyword in C++
        * `typename` can get enhanced by concepts
+ Concepts can use traits classes for their definition but they do not rely on them
    - You can also use other mechanics for defining your concept, besides traits classes

### The `requires` keyword
+ Is commonly used with concepts but existed before C++20 (when C++ concepts were introduced)
+ `requires` can be used as follows:
    - `requires(T t) {}`
        * `requires`: Is the keyword itself
        * `T t`: We handover a (templated) class T and use it within the code as 
        * `{ ... }`: Here we can define our requirements to the instance `t`
+ But `requires` is always used in combination with C++ templates
+ Example _`requires` without concepts_:
```
#include <iostream>

template <typename T>
void print_if_int(const T& value) {
    if constexpr (requires { std::cout << value; }) {
        std::cout << value << std::endl;
    } else {
        std::cout << "Not an int" << std::endl;
    }
}

int main() {
    int x = 42;
    double y = 3.14;

    print_if_int(x);  // Dies wird den Wert ausgeben.
    print_if_int(y);  // Dies wird "Not an int" ausgeben.
    return 0;
}

```
    - Remarks:
        * `constexpr`: Is used to tell the compiler that a routine can be evaluated at compile time. This enables the compiler to optimize the code for runtime speed. Also the compile speed itself will get faster
        * `constexpr` can be used for variables as well as for functions where the programmer knows in advance that the expression can be evaluated at compile time
## C++20 STL concepts
+ C++ defines some standart concepts that just can be used without defining your own concept. These can be found within the header `#include <concepts>` (C++20 or newer)
    - An overview can be found [here](https://en.cppreference.com/w/cpp/header/concepts)