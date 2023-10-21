#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "Observer.hpp"
#include "Observable.hpp"

using namespace std;
using namespace boost;

// observable
class Person : public Observable<Person> {
	int age;
	bool canVote;

public:
	Person(int initAge) : age(initAge) {}

	int get_age() const {
		return age;
	}
	void set_age(int ageUpdate) {
		if (age != ageUpdate) {
			// update age as before
			age = ageUpdate;
			notify_field(*this, "age"); // after inheriting from the observable base class, we just need to use the notfication functions ob the Observable<T> class within our business logic implementation
		
			// dependend field event trigger
			bool oldCanVote = canVote;
			if (get_can_vote() != oldCanVote) {
				canVote = get_can_vote();
				notify_field(*this, "can_vote");
			}
		}
	}

	bool get_can_vote() const {
		return (age >= 16);
	}

	/*
	void setOnline(bool online){
		if (online) {
			notify_isOnline(*this);
		}
	}
	*/
};

// observer
class AgeObserverCLI : public Observer<Person>
{
public:
	void field_changed(Person& source, const std::string& fieldname) override {
		if (fieldname == "age") {
			std::cout << "Age has changed to " << source.get_age() << std::endl;
		}
		else if (fieldname == "can_vote") {
			if (source.get_can_vote()) {
				std::cout << "Person can vote now" << std::endl;
			}
			else {
				std::cout << "Person can not vote anymore" << std::endl;
			}
		}
	}

	/*
	// example for other observable API methods
	void online_state_changed(Person& source) {
		source->send_alive_requests();
	}
	*/
};

int main()
{
	Person person{ 10 };
	AgeObserverCLI cliObs;
	person.subscribe(cliObs);
	person.set_age(15);
	person.set_age(16); // this invokes the dependend event on the age can_vote - this setter will invoke the notify functionallity two times after another
	person.set_age(17);
	person.unsubscribe(cliObs);
	return 0;
}