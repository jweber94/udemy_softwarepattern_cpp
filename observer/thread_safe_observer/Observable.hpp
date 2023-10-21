#pragma once

#include <vector>
#include <string>
#include <mutex>

// forward declaration to the corresponding observer API
template<typename>
class Observer;

/*
	All of the Observable functionallity is encapsulated within the Observable
	template class
*/
template<typename T> // type of the class that should implement the observable
class Observable {
public:
	void notify_field(T& source, const std::string& field_name) {
		std::scoped_lock<std::mutex> lck(mtx);
		for (auto it : observer_list) {
			if (it != nullptr) {
				it->field_changed(source, field_name);
			}
		}
	}
	// void notify_isOnline(T& source) { for (auto it : observer_list){ it->online_state_changed(source) }}; // example for the enhancement of the Observable API
		// we might use a prototype pattern for the different kinds of events that can be fired by the observable
	void unsubscribe(Observer<T>& observer) {
		/* Basic implementation - not robust against reentrency problem */
		// std::scoped_lock<std::mutex> lck(mtx);
		//observer_list.erase(std::remove(observer_list.begin(), observer_list.end(), observer), observer_list.end());
		
		/* Easy fix */
		auto it = std::find(std::begin(observer_list), std::end(observer_list), &observer);
		if (it != std::end(observer_list)) {
			*it = nullptr;
		}
	}

	void subscribe(Observer<T>& observer) {
		std::scoped_lock<std::mutex> lck(mtx);
		observer_list.push_back(observer);
	}
private:
	std::vector<Observer<T>&> observer_list;
	std::mutex mtx;
};