#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "Foo.hpp"

using namespace std;
using namespace boost;


int main()
{
	Foo bar;
	bar.say_hello();
	return 0;
}