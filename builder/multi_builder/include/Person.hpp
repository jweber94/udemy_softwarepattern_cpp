#pragma once
#include <string>

#include "PersonBuilder.hpp"

class PersonBuilder;
class PersonJobBuilder;
class PersonAddressBuilder;

class Person {
private:
	// address
	std::string street_address, post_code, city;
	// employment
	std::string company_name, position;
	std::size_t annual_income{ 0 };

	Person(); // private constructor to forbid the creation without a PersonBuilder

public:
	static PersonBuilder create() { // API for the person creation
		return PersonBuilder();
	}

	// builder friends
	friend class PersonBuilder;
	friend class PersonJobBuilder;
	friend class PersonAddressBuilder;
};