#include <iostream>

#include "PersonBuilder.hpp"
#include "PersonJobBuilder.hpp"
#include "PersonAddressBuilder.hpp"
#include "Person.hpp"


int main() {
	
	Person pers = Person::create()
		.lives().at("StreetOne")
				.in("Munic")
				.with_postcode("1263")
		.works().company("Leica")
				.position("Engineer")
				.income(100000);

	return 0;
}