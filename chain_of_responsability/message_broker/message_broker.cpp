#include <iostream>
#include <string>
#include <boost/signals2.hpp>

struct Query {
	std::string m_creatureName; // forward declaration
	enum Argument { // definition of what can be queryed
		attack,
		defence
	} m_argument; // define and create member of the enum at the same time
public:
	int m_result; // this is the adjusted data by the query - the most recent data is safed within the query, NOT within the instances itself

	Query(const std::string& creatureName, Argument arg, int result) :
		m_result(result),
		m_argument(arg),
		m_creatureName(creatureName) 
	{}
};

struct Game { // mediator - this is our message broker 
public:
	boost::signals2::signal<void(Query&)> m_querys;// define a signal within the game that all instances within the game can subscribe to
		// the signal is what all instances within the game can subscribe to
};

struct Creature {
	Game& m_game; // all other instances within the game can adjust querys that are made within the game that affects a Creature instance
	int m_attack; // this is only the baseline data - they can be modifyed by a modifyer but these are stay the same though out the game
	int m_defence;
	std::string m_name;
public:
	Creature(Game& game, int attack, int defence, const std::string& name) :
		m_game(game),
		m_attack(attack),
		m_defence(defence),
		m_name(name) {}

	int getAttack() const { // here we access the actual data from the query and not the data from within the instance itself since these data is only the baseline value and not the value within the game (which depends on losely coupled modifyers)
		Query q(m_name, Query::Argument::attack, m_attack); // m_result will be the modifyer adjusted value of the base attack value of this Creature instance
		m_game.m_querys(q); // here we invoke the signal with our query from the creature to send a message to the mediator/message broker
			// m_game.m_querys(q) invokes the signal with the Query object q - this invokes all subscribed lambda functions (of the modifyers) which take the Query instance q into account
		return q.m_result;
	}

	friend std::ostream& operator<<(std::ostream& os, const Creature& creature) {
		os << "creature name = " << creature.m_name << "; attack = " << creature.getAttack(); // here the query is done every time when the << operator is called
		return os;
	}
};

// basic COR class - just to have the basic functionallity clustered as a base class
struct CreatureModifyer { // the modifyer listens to the message broker (aka the game object) on new messages on our m_querys topic
	Game& m_game;
	Creature& m_creature;
public:
	CreatureModifyer(Game& game, Creature& creature) : // linking of the modifyer to the message broker and the concrete creature
		m_game(game),
		m_creature(creature) 
	{}
	virtual ~CreatureModifyer() = default;
};

// differenciations of the modifyers
class DoubleAttackModifyer : public CreatureModifyer {
	boost::signals2::connection m_conn;

public:
	DoubleAttackModifyer(Game& game, Creature& creature) :
		CreatureModifyer(game, creature) 
	{
		m_conn = game.m_querys.connect(
			[&](Query& q) // CAUTION: not a const Query& because we modify the m_result of the query
			{
				if (q.m_creatureName == creature.m_name &&
						q.m_argument == Query::Argument::attack) 
				{
					q.m_result *= 2;
				}
			}
		);
	}

	~DoubleAttackModifyer() {
		m_conn.disconnect(); // unsubscribe on destruction
	}
};


int main() {
	Game game;
	Creature goblin{ game, 2, 2, "Strong Goblin" };
	std::cout << goblin << std::endl;
	{
		DoubleAttackModifyer dam(game, goblin); // as long as the dam is in scope, all querys (called by .getAttack() within the << operator) will be done with the dam invoked
		std::cout << goblin << std::endl;
	}
	std::cout << goblin << std::endl;
	return 0;
}