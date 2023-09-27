#pragma once

#include "Person.hpp"

#include "PersonAddressBuilder.hpp"
#include "PersonJobBuilder.hpp"
/* This is actually a builder facade */

// forward declaration
class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase { // we want to inherit from PersonBuilderBase further down the line to make a fluent API of different Builders
protected:
	Person& _person;
public:
	PersonBuilderBase(Person& person) :
	_person(person)
	{}

	PersonJobBuilder works() const {
		return PersonJobBuilder{ _person };
	}

	PersonAddressBuilder lives() const {
		return PersonAddressBuilder{ _person };
	}

	// needed to cast the PersonBuilder / PersonBuilderBase to a Person, aka get the instance out of the builder after it is constructed
	operator Person() const {
		return std::move(_person);
	}
};

// PersonBuilder is according to the single responsability principle responsible for holding the instance and handing it over to all individual builders via its base class
class PersonBuilder : public PersonBuilderBase {
private:
	Person _p;

public:
	PersonBuilder() :
	PersonBuilderBase(_p) {} // handing over to the base class to distribute the reference to the _p instance to all other builder functionallities
};