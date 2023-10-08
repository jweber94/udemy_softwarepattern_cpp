#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <boost/lexical_cast.hpp>
#include "di.hpp"

using namespace std;
using namespace boost;

struct IFoo {
	virtual std::string name() = 0;
};

struct Foo : public IFoo {
	static int _id;

	Foo() 
	{
		++_id;
	}

	std::string name() override {
		return "foo"s + boost::lexical_cast<std::string>(_id);
	}
};

int Foo::_id{0}; // We need to initialize static members outside of the class that contains it - if not we get an "undefined reference"

struct Bar {
	std::shared_ptr<IFoo> _pFoo;
}; // constructor is Bar(std::shared_ptr<IFoo>) on default


int main(int argc, char* argv[])
{
	auto injector = boost::di::make_injector(
		boost::di::bind<IFoo>().to<Foo>().in(boost::di::singleton));
		// With the dependency injection framework boost::di we can define the lifetime as a singleton without writing the singleton code ourselfs
		// That enables a better testability of the users of our singleton, since we can inject dummy singletons/no singletons in case of a unit test (which we have done manually in the last tutortial)
	
	std::shared_ptr<Bar> bar1 = injector.create<std::shared_ptr<Bar>>();
	std::shared_ptr<Bar> bar2 = injector.create<std::shared_ptr<Bar>>();


	std::cout << boolalpha << (bar1->_pFoo.get() == bar2->_pFoo.get()) << std::endl;
	return 0;
}