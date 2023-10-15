#pragma once

#include <string>

class Person {
public:
	class PersonImpl; // hide implementation - forward declaration to be able to create a pointer to that class without the need of defining it within the header so the user of the library cannot see the implementation details

	/* To avoid exposing the source code and thereby the interlectual property, we do not define ANY method in the header - this is all done within the cpp which is not deployed to the user of the library */

	Person(const std::string&& name);
	~Person();

	void greet();

private:
	std::string _name;
	PersonImpl* _pImpl;
};
