#include <iostream>

#include "Person.hpp"
#include "ChatRoom.hpp"

int main() {
	ChatRoom room;
	Person john{ "John" };
	Person jane{ "Jane" };

	room.join(&john);
	room.join(&jane);

	john.say("Hi room");
	jane.say("oh, hey john");

	Person simon{ "simon" };
	room.join(&simon);

	simon.say("hi everyone");

	jane.pm("simon", "glad you found us");

	std::cout << "Hello World\n";
	return 0;
}