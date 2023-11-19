#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/bimap.hpp>

using namespace std;
using namespace boost;

typedef uint32_t key;

struct User {
public:
	// constructor
	User(const std::string& firstName, const std::string& lastName) :
		_firstName(add(firstName)),
		_lastName(add(lastName))
	{}

	// getters and setters
	const std::string& get_first_name() const {
		return _names.left.find(_firstName)->second;
	}
	const std::string& get_last_name() const {
		return _names.left.find(_lastName)->second;
	}

	friend std::ostream& operator<<(std::ostream& os, const User& user) {
		os << "firstName = " << user.get_first_name() << "(" << user._firstName << ")" << "; lastName = " << user.get_last_name() << " (" << user._lastName << ")";
		return os;
	}

private:
	key _firstName;
	key _lastName;

protected:
	static boost::bimap<key, std::string> _names;
	static key _seed;

	static key add(const std::string& str) {
		auto it = _names.right.find(str);
		if (it == _names.right.end()) { // add the string and associate it with the next key if it is not already within our bimap
			key id = ++_seed;
			_names.insert({_seed, str});
			return id;
		}
		return it->second; // return the key behind the string that were requested to be added (because it is already added)
	}

};

// initialize static members (need to be done outside the class)
key User::_seed{ 0 };
boost::bimap<key, std::string> User::_names{};

int main()
{
	User user1{ "John", "Smith" };
	User user2{ "Jane", "Smith" };

	std::cout << "user 1 is " << user1 << std::endl;
	std::cout << "user 2 is " << user2 << std::endl;

	return 0;
}