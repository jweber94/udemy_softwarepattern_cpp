#include <iostream>
#include <map>
#include <vector>
#include <utility>

// state definitions
enum class State {
	off_the_hook,
	connecting,
	connected,
	on_hold,
	on_hook
};

inline std::ostream& operator<<(std::ostream& os, const State& s) {
	switch (s) {
	case State::off_the_hook:
		os << "off the hook";
		break;
	case State::connecting:
		os << "connecting";
		break;
	case State::connected:
		os << "connected";
		break;
	case State::on_hold:
		os << "on hold";
		break;
	case State::on_hook:
		os << "on the hook";
		break;
	}
	return os;
}

// state transition triggers which cases our object state to transition from one to another
enum class Triggers {
	call_dialed,
	hung_up,
	call_connected,
	placed_on_hold,
	taken_off_hold,
	left_message,
	stop_using_phone
};

inline std::ostream& operator<<(std::ostream& os, const Triggers t) {
	switch (t) {
	case Triggers::call_dialed:
		os << "call dialed";
		break;
	case Triggers::hung_up:
		os << "hung up";
		break;
	case Triggers::call_connected:
		os << "call connected";
		break;
	case Triggers::placed_on_hold:
		os << "placed on hold";
		break;
	case Triggers::taken_off_hold:
		os << "taken of hold";
		break;
	case Triggers::left_message:
		os << "left message";
		break;
	case Triggers::stop_using_phone:
		os << "stop using the phone";
		break;
	}
	return os;
}


int main() {
	// For simplistic reasons, we implement our state machine directly within the main function/entrypoint of our program
	
	/* Defining state machine transition rules */
	std::map<State, std::vector<std::pair<Triggers, State>>> fsm_rules{};

	fsm_rules.insert(
		{ 
			State::off_the_hook, 
			{
				{ Triggers::call_dialed, State::connected },
				{ Triggers::stop_using_phone, State::on_hook }
			}
		}
	);

	fsm_rules.insert(
		{
			State::connecting,
			{
				{ Triggers::hung_up, State::off_the_hook },
				{ Triggers::call_connected, State::connected }
			}
		}
	);

	fsm_rules.insert(
		{
			State::connected,
			{
				{ Triggers::left_message, State::off_the_hook},
				{ Triggers::hung_up, State::off_the_hook },
				{ Triggers::placed_on_hold, State::on_hold }
			}
		}
	);

	fsm_rules.insert(
		{
			State::on_hold,
			{
				{ Triggers::taken_off_hold, State::connected },
				{ Triggers::hung_up, State::off_the_hook }
			}
		}
	);

	/* Implementing the state machine main loop */
	// defining start and termination state of this application
	State currentState{ State::off_the_hook };
	State exitState{ State::on_hook };

	while (true) {
		std::cout << "The phone is currently " << currentState << std::endl;

	select_trigger:
		std::cout << "Please select the trigger" << std::endl;
		int i = 0;
		// printout all valid triggers to the terminal to let the user choose
		for (auto item : fsm_rules.at(currentState)) {
			std::cout << i++ << ", " << item.first << std::endl;
		}

		int input;
		std::cin >> input;
		if ((input < 0) || ((input + 1) > fsm_rules.at(currentState).size())) {
			std::cout << "Invalid requested trigger!" << std::endl;
			goto select_trigger;
		}

		currentState = fsm_rules.at(currentState).at(input).second;

		if (currentState == exitState) {
			std::cout << "Exit state reached" << std::endl;
			break;
		}
	}
	

	return 0;
}