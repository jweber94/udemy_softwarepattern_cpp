#include <iostream>

struct Creature {
	std::string _name;
	int _attack;
	int _defence;

	Creature(const std::string& name, int attack, int defence) :
		_name(name),
		_attack(attack),
		_defence(defence) 
	{}

	friend std::ostream& operator<<(std::ostream& os, const Creature& creature) {
		os << "name = " << creature._name << "; attack = " << creature._attack << "; defence = " << creature._defence << std::endl;
		return os;
	}
};


class CreatureModifyer {
	CreatureModifyer* _next{ nullptr };

protected:
	Creature& _creature;

public:
	CreatureModifyer(Creature& creature) :
		_creature(creature) 
	{}

	void add(CreatureModifyer* cm) { // add an element to the end of the singly linked list
		if (_next) { // go through the list until the end
			_next->add(cm);
		}
		else { // add the modifyer to the end of the list
			_next = cm;
		}
	}

	virtual void handle() { // this is the default implementation: if nothing is defined for our (inherited) modifyer, just do nothing and go to the next chain element - to enforce this, this method is virtual
		if (_next) { // if there is another element in the chain, just invoke the next handle/chain element
			_next->handle();
		}
	}
};


class DoubleAttackModifyer : public CreatureModifyer {
public:
	DoubleAttackModifyer(Creature& creature) :
		CreatureModifyer(creature)
	{}

	void handle() override {
		// do something within the concrete handle
		_creature._attack *= 2;
		// walk through the chain
		CreatureModifyer::handle(); // invoke the default implementation of the base class
		return;
	}
};

class IncreasedDefenceModifyer : public CreatureModifyer {
public:
	IncreasedDefenceModifyer(Creature& creature) :
		CreatureModifyer(creature)
	{}

	void handle() override {
		// Do something with the modifyer
		if (_creature._attack <= 2) {
			_creature._defence++;
		}
		// walk to next chain element
		CreatureModifyer::handle();
		return;
	}
};

class NoBonusesModifyer : public CreatureModifyer {
public:
	NoBonusesModifyer(Creature& creature) :
		CreatureModifyer(creature)
	{}

	void handle() override {
		std::cout << "Stopping the execution of all bonuses" << std::endl;
	}
};

int main() {
	Creature goblin{ "Goblin", 1, 1 };
	CreatureModifyer root{ goblin };

	DoubleAttackModifyer r1{ goblin };
	DoubleAttackModifyer r1_2{ goblin };
	IncreasedDefenceModifyer r2{ goblin };
	NoBonusesModifyer r3{ goblin };

	root.add(&r1);
	root.add(&r3);
	root.add(&r1_2); // this modifyer will not get invoked because of the no bonuses modifyer
	root.add(&r2);   // same here

	root.handle(); // invoke the chain

	std::cout << goblin << std::endl;
	return 0;
}