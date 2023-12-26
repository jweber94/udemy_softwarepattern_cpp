# pragma once

#include <vector>
#include <string>

struct ChatRoom;

struct Person {
	ChatRoom* room{ nullptr }; // since everything is public in a struct, we do not need to have a setter for the room pointer. We just can set it on the ChatRoom s join function directly to the this pointer of the chat room
	std::vector<std::string> message_log;
	std::string name;

	Person(const std::string& name) :
		name(name)
	{}

	void say(const std::string& message) const;
	void pm(const std::string& targetName, const std::string& message) const;
	void receive(const std::string& origin, const std::string& incomingMessage);

	bool operator==(const Person& rhs) const;
	bool operator!=(const Person& rhs) const;
};