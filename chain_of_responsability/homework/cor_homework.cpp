#include <iostream>
#include <vector>

struct Creature;
struct Game
{
    std::vector<Creature*> creatures;
};

struct StatQuery // result of the query holds the COR updated value based by the (unchanged) base_attack or base_defence
{
    enum Statistic { attack, defense } statistic;
    int result;
};

struct Creature
{
protected:
    Game& game;
    int base_attack, base_defense;

public:
    Creature(Game& game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
        base_defense(base_defense) {}
    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
    virtual bool is_goblin_king() { return false; }
};


class Goblin : public Creature
{
public:
    Goblin(Game& game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

    Goblin(Game& game) : Creature(game, 1, 1) {} // default constructor if you just handover a game and do not set any attack or defence values

    int get_attack() override {
        StatQuery attackQuery{ StatQuery::Statistic::attack, base_attack };
        for (auto it : game.creatures) {
            if (it->is_goblin_king() && (it != this)) {
                // Goblin King detected
                attackQuery.result += 1;
            }
        }
        return attackQuery.result;
    }

    int get_defense() override {
        StatQuery defenceQuery{ StatQuery::Statistic::defense, base_defense };
        for (auto it : game.creatures) {
            if ((dynamic_cast<Goblin*>(it) != nullptr) && (it != this)) {
                defenceQuery.result += 1;
            }
        }
        return defenceQuery.result;
    }

    bool is_goblin_king() override {
        return false;
    }
};

class GoblinKing : public Goblin
{
public:
    GoblinKing(Game& game) : Goblin(game, 3, 3) {}
    
    bool is_goblin_king() override {
        return true;
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