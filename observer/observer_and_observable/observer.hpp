#pragma once

// this is our observer interface/abstraction that is able to receive events from the observable
template<typename T> 
struct Observer { // the observer need to inherit from this with the template argument as the class of the observable
	virtual void field_changed(T& source, const std::string& field_name) = 0; // the observable need to implement this interface
		// this is the abstraction for the metho that is called whenever something happened on the observable - the observable actively calls in its template definition this method name
};