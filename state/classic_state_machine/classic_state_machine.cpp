#include <iostream>

// forward declaration
class LightSwitch;

struct State {
	/* In the base class we define the behaviour if we are already within the target state. This is cause by a clever usage of the polymorphism of the State class. We overload only the opposite operation of the derived state class */
	virtual void on(LightSwitch* ls) // keep in mind - the virtual says that our object is threated polymorphicly regarding this method - if we have an override and an object of a derived class, the method of the derived class is executed. If we do not mark the method as virtual, an object, addressed via a pointer of the base class will execute the method of the base class (even if an overload for that specific object (of the derived class) is defined. That is not what we expect from a polymorphic language like C++. Basically, virtual allows the compiler to enables runtime bindings of methos (aka that methods are resolved via a vtable)
	{
		std::cout << "State is already on" << std::endl;
	}
	virtual void off(LightSwitch* ls)
	{
		std::cout << "State is already off" << std::endl;
	}

};

struct OnState : public State {
	OnState() {
		std::cout << "Light is turned on" << std::endl;
	}

	void off(LightSwitch* ls) override; // use the default implementation if we try to call on from the on state
};

struct OffState : public State {
	OffState() {
		std::cout << "Light is turned off" << std::endl;
	}

	void on(LightSwitch* ls) override;
};


/* The LightSwitch acts as a mediator between state objects */
class LightSwitch {
	State* state;

public:
	LightSwitch() {
		state = new OffState();
	}

	void set_state(State* newState) {
		state = newState;
	}

	void on();
	void off();
};

void LightSwitch::on() {
	state->on(this);
}

void LightSwitch::off() {
	state->off(this);
}

void OnState::off(LightSwitch* ls) {
	std::cout << "Switching light off..." << std::endl;
	ls->set_state(new OffState()); // reassign the pointer to the state of the LightSwitch instance
	delete this; // commonly an antipattern to delete yourself but ok for this example
}

void OffState::on(LightSwitch* ls) {
	std::cout << "Switching light on..." << std::endl;
	ls->set_state(new OnState());
	delete this;
}

int main() {
	LightSwitch ls; // light is off at construction
	ls.on();

	ls.off();
	ls.off(); // default implementation will be called

	return 0;
}