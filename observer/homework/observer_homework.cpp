#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Observer implementation
struct IRat {
    virtual void setAttackVal(int newAttackVal) = 0;
};

// Observable
struct Game
{
public:
    void notify() {
        for (auto rat : ratsInGame) {
            rat->setAttackVal(ratsInGame.size());
        }
    }

    void subscribe(IRat& rat) {
        ratsInGame.push_back(&rat);
        notify();
    }

    void unsubscribe(IRat& rat) {
        IRat* ratToDelete = &rat;
        ratsInGame.erase(std::remove_if(ratsInGame.begin(), ratsInGame.end(),
            [&ratToDelete](const IRat* rat) {
                return rat == ratToDelete;
            }), ratsInGame.end()
        );
        notify();
    }

private:
    std::vector<IRat*> ratsInGame;
};

// Observer
struct Rat : IRat
{
    Game& game;
    int attack{ 1 };

    Rat(Game& game) : game(game)
    {
        game.subscribe(*this);
    }

    ~Rat()
    {
        game.unsubscribe(*this);
    }

    void setAttackVal(int newAttackVal) {
        attack = newAttackVal;
    }
};


int main()
{
    Game testGame;

    Rat* rat1 = new Rat(testGame);
    std::cout << "Attack of rat 1 is " << rat1->attack << std::endl;
    Rat* rat2 = new Rat(testGame);
    std::cout << "Attack of rat 1 is " << rat1->attack << std::endl;
    Rat* rat3 = new Rat(testGame);
    std::cout << "Attack of rat 1 is " << rat1->attack << std::endl;

    delete rat2;
    std::cout << "Attack of rat 1 is " << rat1->attack << std::endl;

	return 0;
}