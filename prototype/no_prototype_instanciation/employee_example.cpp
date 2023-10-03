#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Address {
	std::string _street;
	std::string _city;

	int _suite;

	Address() = default;

	Address(std::string street, std::string city, int suite):
	_street(street),
	_city(city),
	_suite(suite) {}

	// copy constructor
	Address(const Address& address) {
		_street = address._street;
		_city = address._city;
		_suite = address._suite;
	}

	Address& operator=(const Address& address) {
		Address result;
		result._city = address._city;
		result._street = address._street;
		result._suite = address._suite;
		return result;
	}

};


struct Contact {
	std::string _name;
	Address* _address;

	// needed to create the result in the copy assignment operator
	Contact() = default;

	Contact(const std::string& name, Address* address) :
	_name(name),
	_address(address)
	{}

	// copy constructor
	Contact(const Contact& contact) :
	_name{contact._name},
	_address{new Address(*contact._address)} //= new Address(contact._address->_street, contact._address->_city, contact._address->_suite); // this is what the deep copy is all about
	{}
	// copy assignment operator
	Contact& operator=(const Contact& contact) {
		Contact result;
		result._name = contact._name;
		result._address = new Address(contact._address->_street, contact._address->_city, contact._address->_suite); // this is what the deep copy is all about
		return result;
	}

	friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
		os << "name: " << contact._name << "; city: " << contact._address->_city << "; street: " << contact._address->_street << "; suite: " << std::to_string(contact._address->_suite);
		return os;
	}

};


int main()
{
	Contact john{"John Doe", new Address{"123 East Str", "London", 123}};	// complicated constructor
	Contact jane{"Jane Doe", new Address{"123 East Str", "London", 234}};	// called multiple times with just two parameter variations
	
	// better approach: reuse an already created employee
	//Contact jenny = john;
	Contact jenny{john}; // john is our prototype in that case - the derivation of jenny from john is a very basic example of the prototype design pattern
	jenny._name = "Jenny Smith";
	jenny._address->_suite = 112; // if we have not had a deep copy, the suite number of the prototype (john) will get overwritten by the suite number of jenny which is wrong behaviour

	std::cout << john << std::endl << jane << std::endl << jenny << std::endl;

	return 0;
}