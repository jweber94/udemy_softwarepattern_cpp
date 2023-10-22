#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <array>
#include <algorithm>
#include <numeric>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

// anti pattern example
/*
class Creature {
	int strength;
	int intelligence;
	int agility;

public:
	// getter and setter
	int get_strength() const {
		return strength;
	}
	void set_strength(int newStrength) {
		strength = newStrength;
	}
	void set_intelligence(int newIntelligence) {
		intelligence = newIntelligence;
	}
	int get_intelligence() const {
		return intelligence;
	}
	void set_agility(int newAgility) {
		agility = newAgility;
	}
	int get_agility() const {
		return agilty;
	}

	// statistics
	// as we can see, we have to adjust all statistics methods if we add another attribute and the code gets very messy
	double sum() const {
		return agility + intelligence + strength;
	}
	double average() const {
		return sum() / 3.0;
	}
	int max() const {
		return ::max(::max(strength, agility), intelligence);
	}
};
*/

// array backed properties pattern
class Creature {
	enum Abilities { // normal enum instead of enum class to have the ability to indirectly cast to int while using it to access properties
		strength,
		agility,
		intelligence,
		count // terminating element that can be accessed to get the total amont of properties of the array backed property of the class
	};

	std::array<int, Abilities::count> _properties;

public:
	// getter and setter
	int get_strength() const {
		return _properties.at(Abilities::strength); // std::array::at() can be a rvalue as well as a lvalue
	}
	void set_strength(int newStrength) {
		_properties.at(Abilities::strength) = newStrength;
	}
	void set_intelligence(int newIntelligence) {
		_properties.at(Abilities::intelligence) = newIntelligence;
	}
	int get_intelligence() const {
		return _properties.at(Abilities::intelligence);
	}
	void set_agility(int newAgility) {
		_properties.at(Abilities::agility) = newAgility;
	}
	int get_agility() const {
		return _properties.at(Abilities::agility);
	}

	double sum() const {
		return std::accumulate(_properties.begin(), _properties.end(), 0);
	}

	double avg() const {
		return sum() / (double)(Abilities::count);
	}

	double max() const {
		return *std::max_element(_properties.begin(), _properties.end());
	}
};


int main()
{
	Creature orc;
	orc.set_strength(19);
	orc.set_agility(7);
	orc.set_intelligence(1);

	std::cout << "The orc has the average ability of " << orc.avg() << std::endl;
	std::cout << "The orc has the max ability of " << orc.max() << std::endl;
	std::cout << "The orc has the sum ability of " << orc.sum() << std::endl;

	return 0;
}