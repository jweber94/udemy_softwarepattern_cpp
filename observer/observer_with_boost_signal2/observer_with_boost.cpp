#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost;

template<typename T>
struct Observable2 {
	boost::signals2::signal<void(T&, const std::string&)> field_changed;
};

class Person2 : public Observable2<Person2>
{
	int age;

public:
	int get_age() const {
		return age;
	}

	void set_age(int new_age) {
		if (new_age != age) {
			this->age = new_age;
			this->field_changed(*this, "age");
		}
	}
};


int main()
{
	Person2 person;
	
	boost::signals2::connection connectionInterface = 
		person.field_changed.connect(
			[](Person2 p, const std::string field_name) 
			{
				std::cout << "field name = " << field_name << " has changed" << std::endl;
			}
		);

	person.set_age(29);
	connectionInterface.disconnect();

	return 0;
}