#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "Person.hpp" // main.cpp simulates the user of the library

using namespace std;
using namespace boost;

int main()
{
	Person jens("jens");
	jens.greet();

	return 0;
}