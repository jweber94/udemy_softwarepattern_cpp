#pragma once

#include <string>
#include <vector>

template <typename>
struct Observer;

template<typename T>
struct Observable {
	std::vector<Observer<T>*> observers; // list of Observers of different types (possible) but all need to implement the Observer interface which defines the method(s) that an observable can call

public:
	void notify(T& source, const std::string& field_name) { // since we hand over the source as the reference to the instance of the observable and forward it to the observer template, we have acces in the observer code to the full instance of the observable - the field_name defines which has changed on the handed over instance
		for (auto observer : observers) {
			observer->field_changed(source, field_name); // here is source handed over to the observer template
				// this is the call to the observer abstraction within the observable
		}
	}

	// adding and removing to and from the list of observers
	void subscribe(Observer<T>& observer) {
		observers.push_back(&observer);
	}

	void unsubscribe(Observer<T>& observer) {
		observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
	}
};