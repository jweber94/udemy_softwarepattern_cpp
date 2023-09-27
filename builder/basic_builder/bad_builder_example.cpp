#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

/* Webserver backend example - serve HTML code */
int main()
{
	// worst approach that does not scale
	std::string text = "hello";
	std::string output;
	output += "<p>";
	output += text;
	output += "</p>";
	std::cout << output << std::endl;

	// better approach to make arbitrary text available via a string array
	std::string wordContent[] = {"hello", "world"}; // content
	std::ostringstream oss;
	oss << "<ul>\n";
	for (auto word : wordContent) {
		oss << "  <li>" << word << "</li>\n";
	}
	oss << "</ul>\n";
	std::cout << oss.str() << std::endl;
	/* The problem with this approach is that we want to put a string together piece by piece */
	return 0;
}