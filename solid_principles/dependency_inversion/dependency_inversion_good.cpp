#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum class Relationship { // low level
	parent,
	child,
	sibling
};

struct Person { // low level
	/* single responsabiliy: manage/structure data for a person */
	std::string _name;
	std::size_t _age;
};

struct RelationshipBrowser { // abstraction that connects the low level modules with the high level module
	virtual std::vector<std::tuple<Person, Relationship, Person>> find_all_childeren_of(const Person& person) = 0;
};

struct Relationships : public RelationshipBrowser { // In order to fulfill the single responsability principle, Relationships are the module where we want to implement the browsing/filtering functionallity
	/* single responsability: deliver processing functionallity */
	
	// members
	std::vector<std::tuple<Person, Relationship, Person>> _relations;
	
	// interface implementation
	std::vector<std::tuple<Person, Relationship, Person>> find_all_childeren_of(const Person& person) override {
		std::vector<std::tuple<Person, Relationship, Person>> result;
		for (auto& [pers1, relation, pers2] : _relations) {
			if (relation == Relationship::child) {
				result.push_back({pers1, relation, pers2});
			}
		}
		return result;
	}

	// class specific functionallity
	void add_parent_and_child(const Person& parent, const Person& child) {
		_relations.push_back({parent, Relationship::parent, child});
		_relations.push_back({child, Relationship::child, parent});
	}
};

struct Research {
	Research(RelationshipBrowser& relBrowser, const Person& pers) {
		for (auto& [pers1, rel, pers2] : relBrowser.find_all_childeren_of(pers)) {
			std::cout << pers._name << " has a child called " << pers2._name << std::endl;
		}
	}
};

int main()
{
	Person parent1{"Melvin", 32}, parent2{"Kora", 29};
	Person child1{"Kevin", 8}, child2{"Chantal", 16};

	Relationships rels;
	rels.add_parent_and_child(parent1, child1);
	rels.add_parent_and_child(parent1, child2);

	// API does not change even when the Relationships implementation changes - as long as it implements the RelationshipBrowser abstraction
	Research reseachInstance(rels, parent1); // rels can be handed over due to polymorphism

	return 0;
}