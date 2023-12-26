#include <iostream>
#include <string>
#include <boost/signals2.hpp>

struct EventData {
	virtual void print() const = 0;
};

struct PlayerScoreData : public EventData {
	std::string player_name;
	int goals_scored_so_far;

	PlayerScoreData(const std::string& playerName, int goalsSoFar) :
		player_name(playerName),
		goals_scored_so_far(goalsSoFar)
	{}

	void print() const override {
		std::cout << player_name << " has scored (their " << goals_scored_so_far << " goal)" << std::endl;
	}
};

struct Game { // every player and the football coach has a reference to the mediator object, which is in this example the game object
	boost::signals2::signal<void(EventData*)> events;
};

struct Player {
	Game& game;
	std::string player_name;
	int goals_so_far{ 0 };

	Player(const std::string& name, Game& game) :
		player_name(name),
		game(game)
	{}

	void score() {
		goals_so_far++;
		PlayerScoreData goalData{ player_name, goals_so_far };
		game.events(&goalData);
	}
};

struct Coach {
	Game& game;

	Coach(Game& game) : game(game) 
	{
		game.events.connect(
			[](EventData* e) 
			{
				PlayerScoreData* ps = dynamic_cast<PlayerScoreData*>(e);
				if (ps != nullptr) { // cast to subclass from abstract base class successfully
					if (ps->goals_scored_so_far < 3) {
						std::cout << "Coach says: well done, " << ps->player_name << std::endl;
					}
				}
			}
		);
	}
};

int main() {
	Game game;
	Player player1("sam", game);
	Coach coach(game);

	player1.score();
	player1.score();
	player1.score(); // no congats after two goals from the coach

	return 0;
}