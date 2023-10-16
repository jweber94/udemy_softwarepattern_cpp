#pragma once

#include "pimpl.hpp"

class Foo
{
    class impl;
    pimpl<impl> impl;
public:
    void say_hello();
};