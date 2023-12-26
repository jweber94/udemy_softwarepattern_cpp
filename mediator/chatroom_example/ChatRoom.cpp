#include "ChatRoom.hpp"
#include <algorithm>

void ChatRoom::broadcast(const std::string& origin, const std::string& message) {
	for (auto& p : people) {
		if (p->name != origin) { // do not send the message to the orgin since it already knows what it has written - that is the reason for the operator== and operator!= within the Person struct
			p->receive(origin, message);
		}
	}
}

void ChatRoom::join(Person* p) {
	std::string join_msg = p->name + " joins the chat";
	this->broadcast("room", join_msg);
	p->room = this;
	people.push_back(p);
}

void ChatRoom::message(const std::string& origin, const std::string& who, const std::string& message) {
	auto target = std::find_if(
		std::begin(people),
		std::end(people),
		[&](const Person* p) {
			return (p->name == who);
		}
	);
	if (target != std::end(people)) {
		(*target)->receive(origin, message);
	}
}