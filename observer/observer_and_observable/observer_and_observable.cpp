#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "observer.hpp"
#include "observable.hpp"

using namespace std;
using namespace boost;

// observable
class Person : public Observable<Person>{
public:
	Person(int init_age) : age{init_age} {}

	int get_age() const {
		return age;
	}

	void set_age(const int new_age) {
		if (new_age == this->age) {
			return;
		}
		this->age = new_age;
		notify(*this, "age"); // the differenciation of the observable needs to explicitly call the notify method of the Observable base class whenever it requires to notify all its subscribers
	}

private:
	int age;
};

// observer - this could be part of an instance that really needs to get notified
struct ConsolePersonObserver : public Observer<Person> {
private:
	void field_changed(Person& source, const std::string& field_name) override { // differenciation what should happen for a particular observer if it gets notified
		if (field_name == "age") {
			std::cout << "Age changed to " << source.get_age() << std::endl;
		}
	}
};


int main()
{
	// example code
	Person person{ 10 };
	ConsolePersonObserver cpo;
	person.subscribe(cpo);

	person.set_age(11);
	person.set_age(12);
	person.unsubscribe(cpo);
	person.set_age(13);

	return 0;
}