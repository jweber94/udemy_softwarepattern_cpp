#include <iostream>
#include <vector>
#include <string>

#include <boost/msm/back/state_machine.hpp>			// backend
#include <boost/msm/front/state_machine_def.hpp>	// frontend
#include <boost/msm/front/functor_row.hpp>			// frontend
#include <boost/mpl/vector.hpp>						// utility needed for the state transition table

// print name
std::vector<std::string> state_names{
	"off hook",
	"connecting",
	"connected",
	"on hold",
	"destroyed"
};

// trigger definitions via objects
struct CallDialed {};
struct HungUp{};
struct CallConnected{};
struct PlacedOnHold{};
struct TakenOffHold{};
struct LeftMessage{};
struct PhoneThrownIntoWall{};

// state machine definition
struct PhoneStateMachine : public boost::msm::front::state_machine_def<PhoneStateMachine> // CRTP (Currious Recurring Template Pattern)
{
	// fields / member variables of the state machine
	bool angry{ true };

	// state definitions
	struct OffHook : public boost::msm::front::state<> {};
	struct Connecting : public boost::msm::front::state<> 
	{
		// we can define with boost::msm some functionallity that should be executed whenever a state is reached or left
		template<class Event, class FSM>
		void on_entry(const Event& event, FSM& fsm) { // even if boost::msm trys to use this method on a state it is NOT an override
			std::cout << "We are connecting" << std::endl;
		}
		/*
		template<class Event, class FSM>
		void on_exit(const Event& event, FSM& fsm) override{

		}
		*/
	};
	struct Connected : public boost::msm::front::state<> {};
	struct OnHold : public boost::msm::front::state<> {};
	struct PhoneDestroyed : public boost::msm::front::state<> {};
	
	struct PhoneBeingDestroyed {
		template<class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const&, FSM&, SourceState&, TargetState&)
		{
			std::cout << "Phone breaks into a million pieces" << std::endl;
		}
	};

	struct CanDestoryPhone
	{
		template<class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const&, FSM& fsm, SourceState&, TargetState&)
		{
			return fsm.angry;
		}
	};

	// transition table
	struct transition_table : public boost::mpl::vector // this sub struct needs to be named exactly to transition_table to get found by boost::msm
		<
			// defining state transition rules as rows
			boost::mpl::vector<OffHook, CallDialed, Connecting>,
			boost::mpl::vector<Connecting, CallConnected, Connected>,
			boost::mpl::vector<Connected, PlacedOnHold, OnHold>,
			boost::mpl::vector<OnHold, PhoneThrownIntoWall, PhoneDestroyed, // idx 0 is the current state, idx 1 is the transition that is called and idx 2 is the target state of this state transition rule
				PhoneBeingDestroyed, CanDestoryPhone> // the fourth and fifth element within the vector describes a state transition action and a guard condition which need to be fulfilled to be able to go to the target state (with index 2 of this vector row)
		>
	{};

	// start state of the FSM
	typedef OffHook initial_state; // needs to be named exactly to initial_state in order to get found by boost::msm - if not, the compiler will moan at you
	
	// define a function that will be called if we cannot go to the desired state (which means that we have no transition rule from the current state to the requested state of the FSM)
	template <class FSM, class Event>
	void no_transition(Event const& e, FSM&, int state) { // needs to be named exactly to no_transition
		std::cout << "No transition from state " << state_names.at(state) << " on event " << typeid(e).name() << std::endl;
	}
};

int main() {
	boost::msm::back::state_machine<PhoneStateMachine> phone;
	
	auto info = [&]() {
		auto i = phone.current_state()[0];
		std::cout << "The phone is currently " << state_names.at(i) << std::endl;
	};

	info();
	phone.process_event(CallDialed{});
	info();
	phone.process_event(CallConnected{});
	info();
	phone.process_event(PlacedOnHold{});
	info();
	phone.process_event(PhoneThrownIntoWall{});
	info();

	return 0;
}