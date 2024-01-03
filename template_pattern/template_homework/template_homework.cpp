#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
using namespace std;

struct Creature
{
    int attack, health;

    Creature(int attack, int health) : attack(attack), health(health) {}
};

struct CardGame
{
    vector<Creature> creatures;

    CardGame(const vector<Creature>& creatures) : creatures(creatures) {}

    // return the index of the creature that won (is a live)
    // example:
    // - creature1 alive, creature2 dead, return creature1
    // - creature1 dead, creature2 alive, return creature2
    // - no clear winner: return -1
    int combat(int creature1, int creature2)
    {
        // fight each other
        hit(creatures.at(creature1), creatures.at(creature2));
        hit(creatures.at(creature2), creatures.at(creature1));
        // check who has won
        if (
            ((creatures.at(creature1).health <= 0) && (creatures.at(creature2).health <= 0)) 
            ||
            ((creatures.at(creature1).health > 0) && creatures.at(creature2).health)
            ) {
            return -1; // both are dead
        }
        else if (creatures.at(creature1).health <= 0) {
            return creature2;
        }
        else {
            return creature1;
        }
    }

    virtual void hit(Creature& attacker, Creature& other) = 0;
};

struct TemporaryCardDamageGame : CardGame
{
    TemporaryCardDamageGame(const vector<Creature>& creatures) : CardGame(creatures) {}

    void hit(Creature& attacker, Creature& other) override {
        int fightResult = (other.health - attacker.attack);
        if (fightResult <= 0) {
            other.health = 0;
        }
    }
};

struct PermanentCardDamageGame : CardGame
{
    PermanentCardDamageGame(const vector<Creature>& creatures) : CardGame(creatures) {}

    void hit(Creature& attacker, Creature& other) override
    {
        other.health -= attacker.attack;
    }
};

int main() {
    std::cout << "Hello World!\n";
    std::vector<Creature> creatures{ {1, 2 }, {1, 3} };

    TemporaryCardDamageGame tmpDamageGame(creatures);
    PermanentCardDamageGame permDamageGame(creatures);

    std::cout << "Wins at combat one: " << permDamageGame.combat(0, 1) << std::endl;;
    std::cout << "Wins at combat two: " << permDamageGame.combat(0, 1) << std::endl;
    for (auto it : permDamageGame.creatures) {
        std::cout << "Health is " << it.health << std::endl;
    }

    return 0;
}