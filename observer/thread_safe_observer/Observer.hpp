#pragma once

#include <string>

template <typename T> // T is the class that we want to observe and that implements the Observable (interface) class that corresponds to this observer (interface) class
class Observer {
public:
	/*
		We can implement methods that are able to receive events from observables that are not fields.
		The main point of it is to have a Observable interface class that suppors also other observable
		methods
	*/
	virtual void field_changed(T& source, const std::string& fieldname) = 0;
	// virtual void online_state_changed(T& source) = 0; // as an example for other interfaces for observables/observers
};