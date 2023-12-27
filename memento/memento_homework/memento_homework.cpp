#include <iostream>

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Token
{
    int value;

    Token(int value) : value(value) {}
};

struct Memento // our snapshot is defined by a set of tokens
{
    vector<shared_ptr<Token>> tokens;
};

struct TokenMachine
{
    vector<shared_ptr<Token>> tokens; // history

    Memento add_token(int value)
    {
        return add_token(make_shared<Token>(value));
    }

    // adds the token to the set of tokens and returns the
    // snapshot of the entire system
    Memento add_token(const shared_ptr<Token>& token)
    {
        if (token) {
            tokens.push_back(token);
        }
        Memento snapshot;
        for (auto t : tokens) {
            snapshot.tokens.emplace_back(std::make_shared<Token>(t->value));
        }
        return snapshot;
    }

    // reverts the system to a state represented by the token
    void revert(const Memento& m)
    {
        tokens.clear();
        for (auto t : m.tokens) {
            tokens.emplace_back(std::make_shared<Token>(t->value));
        }
    }
};


int main() {
	std::cout << "Hello World\n";
	return 0;
}