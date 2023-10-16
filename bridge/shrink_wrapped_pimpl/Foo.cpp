#include "Foo.hpp"

#include <iostream>

class Foo::impl
{
public:
    void say_hello()
    {
        std::cout << "hello";
    }
};

void Foo::say_hello()
{
    impl->say_hello();
}