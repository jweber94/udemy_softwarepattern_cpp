#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Address {
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

	friend class Contact;
};


class Contact {
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

	// for printing with the << operator
	std::string getCity() const {
		return _address->_city;
	}

	std::string getStreet() const {
		return _address->_street;
	}

	int getSuite() const {
		return _address->_suite;
	}


public:
	friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
		os << "name: " << contact._name << "; city: " << contact.getCity() << "; street: " << contact.getStreet() << "; suite: " << std::to_string(contact.getSuite());
		return os;
	}


	class EmployeeFactory {
		public:
			static std::unique_ptr<Contact> new_main_office_employee(const std::string& name, const int suite) {
				static Contact prototype_main_office{"", new Address{"124 East Street", "London", 0}}; // initialized and only invoked the first time the executable encounters this line of code
				return make_main_office_employee(name, suite, prototype_main_office);
			}
		private:
			// utility functions
			static std::unique_ptr<Contact> make_main_office_employee(const std::string& name, const int suite, const Contact& prototype) { // also utility functions needs to be static in order to be instance independend
				std::unique_ptr<Contact> result = std::make_unique<Contact>(prototype); // create a new instance from the prototype via its copy constructor (which is implicitly called by the std::unique_ptr<Contact> invocation)
				// update the deep copied new instance
				result->_name = name;
				result->_address->_suite = suite;
				return result;
			}
	};

};


int main()
{
	std::unique_ptr<Contact> john = Contact::EmployeeFactory::new_main_office_employee("John Doe", 123);
	std::unique_ptr<Contact> jane = Contact::EmployeeFactory::new_main_office_employee("Jane Doe", 124);
	std::unique_ptr<Contact> jenny = Contact::EmployeeFactory::new_main_office_employee("Jenny Smith", 125);

	std::cout << *john << std::endl << *jane << std::endl << *jenny << std::endl;

	return 0;
}