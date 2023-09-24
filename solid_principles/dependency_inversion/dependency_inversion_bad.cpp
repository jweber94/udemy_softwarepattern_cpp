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
	std::string _name;
	std::size_t _age;
};

// low level module - stores the data and delivers functionallity what we can do with its associated data
struct Relationships {
	// members
	std::vector<std::tuple<Person, Relationship, Person>> _relations; // if we make a change in this datastructure, the high level module is also affected by the change - THIS SHOULD BE AVOIDED TO FULFILL THE DEPENDENCY INVERSION PRINCIPLE

	// methods
	void add_parent_and_child(const Person& parent, const Person& child) {
		_relations.push_back({parent, Relationship::parent, child});
		_relations.push_back({child, Relationship::child, parent});
	}
};


struct Research { // high level module - process data with the given functionallity of the low level module
	Research(const Relationships& rels) { // this is bad because we implement a direct dependency to the low level module
		for (auto& [pers1, rel, pers2] : rels._relations) { // here we can see the problem with high level modules that are dependend directly to low level modules: We have to know the exact datastructure of the low level module within the high level module
			if (rel == Relationship::parent) { // this is also bad with regard to the single responsability principle, since the analysis of raltionships should be part of Relationships and not of Research - in this case Research is responsible of analyzing specific relations/represents the business logic while Relationships deliver the functionallty to make the businesslogic work properly
				std::cout << pers1._name << " is the parent of " << pers2._name << std::endl;
			}
		}
	}
};

int main()
{
	Person parent{"Melvin", 32};
	Person child1{"Kevin", 8}, child2{"Chantal", 16};

	Relationships rels;
	rels.add_parent_and_child(parent, child1);
	rels.add_parent_and_child(parent, child2);

	Research reseachInstance(rels); // code is working but very poorly constructed

	return 0;
}