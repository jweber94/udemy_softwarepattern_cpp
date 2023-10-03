#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

	// next lines are needed to serialize the Address class as part of the Contact class
	friend class boost::serialization::access;

	template<class archive>
	void serialize(archive& ar, const unsigned version) { // this is (including the template) needed by boost in order to fulfill the requirements of boost::serialization::access
		// here we define which parts of the Contact class we want to serialize via boost
		ar & _city;
		ar & _street;
		ar & _suite;
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

	friend class boost::serialization::access;

	template<class archive>
	void serialize(archive& ar, const unsigned version) { // this is (including the template) needed by boost in order to fulfill the requirements of boost::serialization::access
		// here we define which parts of the Contact class we want to serialize via boost
		ar & _name;
		ar & _address; // if we try to serialize a class with boost::serialization as a member of another class that should get serialized, the member class needs also have the boost serialization code
			// Boost checks if the members are pointers and does deep copies of it automatically
	}

	friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
		os << "name: " << contact._name << "; city: " << contact.getCity() << "; street: " << contact.getStreet() << "; suite: " << std::to_string(contact.getSuite());
		return os;
	}

};


int main()
{
	// create lambda to save and load Contacts
	auto clone = [](const Contact& c) {
		// serialize Contact
		std::ostringstream oss;
		boost::archive::text_oarchive oa(oss);
		oa << c;
		// just for have a look at the serialized data
		std::cout << "Serialized contact infomation is:" << std::endl << oss.str() << std::endl;

		// deserialize Contact into new object and therefore copying it
		std::istringstream iss (oss.str());
		boost::archive::text_iarchive ia(iss);
		Contact copiedInstance;
		ia >> copiedInstance;

		return copiedInstance;
	};

	Contact john("John Doe", new Address("123 Test Street", "London", 123)); // this is our prototype
	Contact jane = clone(john); // derive from the prototype
	jane._name = "Jane";
	jane._address->_suite = 124;
	std::cout << john << "; " << std::endl << jane << std::endl;

	return 0;
}