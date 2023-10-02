#pragma once

#include <memory>
#include "HotDrink.hpp"

// definition how a favtory for the HotDrink base class should look like
class HotDrinkFactory {
    public:
        virtual std::unique_ptr<HotDrink> make() const = 0; 
};

// differenciations of how the individual classes should get constructed
class TeaFactory : public HotDrinkFactory {
    public:
        std::unique_ptr<HotDrink> make() const override {
            return std::make_unique<Tea>();
        }
};

class CoffeeFactory : public HotDrinkFactory {
    public:
        std::unique_ptr<HotDrink> make() const override {
            return std::make_unique<Coffee>();
        }
};