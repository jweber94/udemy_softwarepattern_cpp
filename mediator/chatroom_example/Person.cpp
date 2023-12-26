#include "Person.hpp"
#include "ChatRoom.hpp"
#include <iostream>

void Person::say(const std::string& message) const {
	room->broadcast(name, message);
}

void Person::pm(const std::string& targetName, const std::string& message) const {
	room->message(name, targetName, message);
}

void Person::receive(const std::string& origin, const std::string& incomingMessage) {
	std::string s {origin + ": \"" + incomingMessage + "\""};
	std::cout << "[" << name << "]" << s << std::endl;
	message_log.emplace_back(s);
}

bool Person::operator==(const Person& rhs) const {
	return name == rhs.name;
}

bool Person::operator!=(const Person& rhs) const {
	return name != rhs.name;
}
