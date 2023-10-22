#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct GraphicObject {
	virtual void draw() = 0;
};

struct Circle : public GraphicObject {
	
	void draw() override {
		std::cout << "Circle" << std::endl;
	}
};

struct Group : public GraphicObject {
	std::vector<GraphicObject*> _objects;
	std::string _name;

	Group(const std::string& name) : _name(name) {}

	void addObject(GraphicObject* pObj) {
		_objects.push_back(pObj);
	}

	void draw() override {
		std::cout << "Group " << _name << " contains:" << std::endl;
		for (auto o : _objects) {
			o->draw();
		}
	}
};

int main()
{
	Group root("root");
	Circle c1, c2, c3;

	root.addObject(&c1);
	root.addObject(&c2);

	Group subgroup("subgroup");
	subgroup.addObject(&c3);

	root.addObject(&subgroup);

	root.draw();

	return 0;
}