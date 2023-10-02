#pragma once

#include <iostream>

// base class for the classes that should get instanciated via the factories
struct HotDrink {
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

// differenciations of the classes that shoud get created
struct Tea : public HotDrink {
    void prepare(int volume) override {
        std::cout << "Take a Tea with " << volume << " ml water" << std::endl;
    }
};

struct Coffee : public HotDrink {
    void prepare(int volume) override {
        std::cout << "Take a coffee with " << volume << " ml water" << std::endl;
    }
};