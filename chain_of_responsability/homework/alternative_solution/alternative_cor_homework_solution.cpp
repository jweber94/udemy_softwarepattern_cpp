#include <iostream>
#include <vector>

/* In this example, we use polymorphism with the query method to achive the correct functionallity instead of defining a separat is_goblin_king method which is more modern C++ like */

struct Creature;

struct Game {
	std::vector<Creature*> creatures;
};

struct StatQuery {
	enum Statistic { attack, defence } statistic;
	int result; // here the modifyed data is stored while the COR is running
};

struct Creature {
protected: // we can access the protected members from a derived class (in contrast to private were this is not possible)
	Game& game;
	int base_attack; // unchangeable base values of every creature during the runtime of the game
	int base_defense;

public:
	Creature(Game& game, int base_attack, int base_defense):
		game(game),
		base_attack(base_attack),
		base_defense(base_defense) 
	{}

	virtual int get_attack() = 0;
	virtual int get_defense() = 0;
	virtual void query(void* source, StatQuery& sq) = 0; // here we define how a query from a creature should look like
};

class Goblin : public Creature // we can access base_attack, base_defence and game& since these are declared protected and not private within the Creature base class
{
private:
	int get_statistic(StatQuery::Statistic stat) {
		StatQuery q{ stat, 0 }; // initial value of the result is 0
		for (auto c : game.creatures) {
			c->query(this, q); // for every creature in the game we update the query object which holds our requested attack or defence value (indicated by the first argument which is handed over by the query method argument)
		}
		return q.result;
	}

public:
	Goblin(Game& game, int attack, int defense) :
		Creature(game, attack, defense) 
	{}

	Goblin(Game& game) :
		Creature(game, 1, 1) 
	{}

	int get_attack() override {
		return get_statistic(StatQuery::Statistic::attack);
	}

	int get_defense() override {
		return get_statistic(StatQuery::Statistic::defence);
	}

	void query(void* source, StatQuery& sq) override {
		if (source == this) { // if we encounter ourselfs while going through all creatures in the game, add our base_ value to the result
			switch (sq.statistic) {
			case StatQuery::attack: // if we query for attack values, we only get the plain base_attack back from the goblins query
				sq.result += base_attack;
				break;
			case StatQuery::defence:
				sq.result += base_defense;
				break;
			default:
				std::cerr << "Invalid StatQuery requested - do notthing" << std::endl;
			}
		}
		else {
			if (sq.statistic == StatQuery::defence) { // defence increases with every goblin within the game other then ourselfs - we do not update the attack value within the goblins query since other goblins do not influence the attack values of the other goblins. Only the defense is affected
				sq.result++;
			}
		}
	}
};

class GoblinKing : public Goblin {
public:
	GoblinKing(Game& game) :
		Goblin(game, 3, 3)
	{}

	void query(void* source, StatQuery& sq) override { // since query is an override to the Creatures query function, it depends on the object within the get_statistic of the goblin (which is also the base class of the GoblinKing class and therefore is also used for every GoblinKing instance) if the GoblinKings query method or the Goblin Query method is used
		if (source != this && sq.statistic == StatQuery::attack) { // if we encounter a normal goblin, it is affected by this goblin kind and increases its attack
			sq.result++;
		}
		else { // looking at the defense value, a goblin king acts as a normal goblin
			Goblin::query(source, sq);
		}
	}
};

int main() {

	Game game;
	Goblin goblin1(game);

	game.creatures.push_back(&goblin1);

	std::cout << "Attack of goblin1 is " << goblin1.get_attack() << "; which should be " << 1 << std::endl;
	std::cout << "Defence of goblin1 is " << goblin1.get_defense() << "; which should be " << 1 << std::endl;

	Goblin goblin2(game);
	Goblin goblin3(game);
	std::cout << "Created two other goblins. This should not affect the goblin within the game!" << std::endl;
	std::cout << "Attack of goblin1 is " << goblin1.get_attack() << "; which should be " << 1 << std::endl;
	std::cout << "Defence of goblin1 is " << goblin1.get_defense() << "; which should be " << 1 << std::endl;

	game.creatures.push_back(&goblin2);
	game.creatures.push_back(&goblin3);

	std::cout << "Added two other goblins to the game. This should affect the other goblins within the game." << std::endl;
	std::cout << "Attack of goblin1 is " << goblin1.get_attack() << "; which should be " << 1 << std::endl;
	std::cout << "Defence of goblin1 is " << goblin1.get_defense() << "; which should be " << 3 << std::endl;

	// goblin king
	GoblinKing goblinKing(game);
	game.creatures.push_back(&goblinKing);
	std::cout << "Added the goblin king to the game" << std::endl;
	std::cout << "Attack of goblin1 is " << goblin1.get_attack() << "; which should be " << 2 << std::endl;
	std::cout << "Defence of goblin1 is " << goblin1.get_defense() << "; which should be " << 4 << std::endl;

	std::cout << "Attack of the goblinKing is " << goblinKing.get_attack() << "; which should be " << 3 << std::endl;
	std::cout << "Attack of the goblinKing is " << goblinKing.get_defense() << "; which should be " << 6 << std::endl;

	return 0;
}