#include "Person.hpp"

#include <iostream>

// this is the hidden implementation with functions, structure and method names that are never visable to the user of the library. That way, we can hide implementation details and secure our interlectual property
class Person::PersonImpl { // PersonImpl is a part of the class definition of Person and therefore needs to get defined within its scope/in its class definition - this is one of the rare occations that a class declaration is done within a cpp file
public:
	PersonImpl() :
		_greetingText("Hello ") 
	{}

	void greetMyName(const std::string& name) {
		std::cout << _greetingText << name << std::endl;
	}

	// here we could implement other secret methods that never gets exposed
private:
	std::string _greetingText;
};


// these implementations of the methods that are defined within the header are not exposed since they are located within the cpp
Person::Person(const std::string&& name) :
	_pImpl(new Person::PersonImpl),
	_name(name)
{}
Person::~Person() {}

void Person::greet() {
	_pImpl->greetMyName(_name);
}