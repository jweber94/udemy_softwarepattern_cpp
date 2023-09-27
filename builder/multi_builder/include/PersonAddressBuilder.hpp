#pragma once

#include "PersonBuilder.hpp"
#include "Person.hpp"

#include <string>

class PersonAddressBuilder : public PersonBuilderBase{
	typedef PersonAddressBuilder Self;

private:

public:
	PersonAddressBuilder(Person& person) :
		PersonBuilderBase(person) {}

	Self& at(std::string street_address) {
		_person.street_address = street_address;
		return *this;
	}

	Self& with_postcode(std::string postcode) {
		_person.post_code = postcode;
		return *this;
	}

	Self& in(std::string city) {
		_person.city = city;
		return *this;
	}
};