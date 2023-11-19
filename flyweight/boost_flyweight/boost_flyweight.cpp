#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/flyweight.hpp>

using namespace std;
using namespace boost;

struct User2 {
	User2(const std::string& firstName, const std::string& lastName) :
		_firstName(firstName),
		_lastName(lastName) 
	{}

	boost::flyweight<std::string> _firstName;
	boost::flyweight<std::string> _lastName;
};

int main()
{
	User2 firstUser{ "John", "Smith" };
	User2 secondUser{ "Jane", "Smith" };
	
	std::cout << firstUser._firstName << "; " << firstUser._lastName << std::endl; // output operator behaves as a normal string
	std::cout << secondUser._firstName << "; " << secondUser._lastName << std::endl;
	// firstUser._firstName.get().c_str() --> .get() gives us the underlying instance and it common API
	// check that we really become a reference not the string over and over again
	std::cout << boolalpha << "First names equal? " << (&firstUser._firstName.get() == &secondUser._firstName.get()) << std::endl;
	std::cout << boolalpha << "Last names equal? " << (&firstUser._lastName.get() == &secondUser._lastName.get()) << std::endl;

	return 0;
}