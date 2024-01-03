#include <iostream>

// meta algorithm and parts that are needed defined as pure virtual to enforce the overlaoding in a derived class which acts as the algorithm/game differenciation
class Game {
public:
	Game(int numPl) : num_players(numPl) {}

	void run() {
		start();
		while (!have_winner()) {
			take_turn();
		}
		std::cout << "Player " << get_winner() << " wins" << std::endl;
	}

protected:
	virtual void start() = 0;
	virtual bool have_winner() = 0;
	virtual void take_turn() = 0;
	virtual int get_winner() = 0;

	int current_player{ 0 };
	int num_players;
};

class Chess : public Game {
public:
	Chess() : Game(2) {}

protected:
	void start() override {
		std::cout << "Starting a game of chess with " << num_players << " players" << std::endl;
	}

	bool have_winner() override {
		return (turn == max_turns);
	}

	void take_turn() override {
		std::cout << "Turn " << turn << " taken by player " << current_player << std::endl;
		++turn;
		current_player = (current_player + 1) % num_players;
	}

	int get_winner() override {
		return current_player;
	}

private:
	int turn{ 0 };
	int max_turns{ 10 };
};



int main() {
	Chess chess;
	chess.run(); // call the skeleton algorithm run() of the base class
	// this will invoke the overwritten pure virtual methods

	return 0;
}