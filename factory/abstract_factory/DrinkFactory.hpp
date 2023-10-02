#pragma once

#include <map>

#include "HotDrink.hpp"
#include "HotDrinkFactory.hpp"

enum class Drinks {
	coffee,
	tea
};

/* Concrete factory of the abstract factory definition in HotDrinkFactory - Facilitate that we use the HotDrinkFactory implemenations */
class DrinkFactory {
    public:
        DrinkFactory() {
            _hotFactories.insert(std::pair<Drinks, std::unique_ptr<HotDrinkFactory>>(Drinks::coffee, std::make_unique<CoffeeFactory>()));
            _hotFactories.insert(std::pair<Drinks, std::unique_ptr<HotDrinkFactory>>(Drinks::tea, std::make_unique<TeaFactory>()));
        }

        std::unique_ptr<HotDrink> make_drink(Drinks drink) {
            std::unique_ptr<HotDrink> retDrink = _hotFactories.at(drink)->make();
            retDrink->prepare(300);
            return retDrink;
        }

    private:
        std::map<Drinks, std::unique_ptr<HotDrinkFactory>> _hotFactories;
};