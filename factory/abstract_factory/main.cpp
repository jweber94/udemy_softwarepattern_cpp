#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "HotDrink.hpp"
#include "HotDrinkFactory.hpp"
#include "DrinkFactory.hpp"

using namespace std;
using namespace boost;

// simulate usage of the factory build pattern API without concrete conclumeration factory (bad practice)
std::unique_ptr<HotDrink> make_drink(Drinks drink) {
	std::unique_ptr<HotDrink> retDrink;
	if (Drinks::coffee == drink) {
		retDrink = CoffeeFactory().make();
	} else if (Drinks::tea == drink) {
		retDrink = TeaFactory().make();
	} else {
		std::cerr << "ERROR: Invalid drink requested" << std::endl;
		return nullptr;
	}
	retDrink->prepare(300);
	return retDrink;
}


int main()
{
	std::unique_ptr<HotDrink> myDrink = make_drink(Drinks::tea); // plain use of API
	std::unique_ptr<HotDrink> myDrink2 = DrinkFactory().make_drink(Drinks::coffee); // more concrete and more elegant way of using the API
	return 0;
}