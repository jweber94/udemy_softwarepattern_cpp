#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

// single responsability - separation of concerns: only to store the data and deliver basic operator functionallity
struct Tag {
	// publics
	/*members */ 
	std::string name, text;
	std::vector<Tag> children;
	std::vector<std::pair<std::string, std::string>> attributes; // vector of key-value pair

	/* methods */
	// print functionallity in C++ style << 
	friend std::ostream& operator<<(std::ostream& os, const Tag& tag) { // << operator to chain std::ostream instances
		os << "<" << tag.name; // opening tag
		// adding all attribues
		for (const auto& attr : tag.attributes) {
			os << " " << attr.first << "=\"" << attr.second << "\"";
		}
		// case tag without second closing tag (notting in between)
		if (tag.children.size() == 0 && tag.text.length() == 0) {
			os << "/>" << std::endl;
		}
		// case text is between opening and closing tag
		else
		{
			os << ">" << std::endl; // finish opening tag
			if (tag.text.length()) { // add text
				os << tag.text << std::endl;
			}
			// recursively call this operator
			for (const auto& child : tag.children) {
				os << child;
			}
			// add closing tag
			os << "</" << tag.name << ">" << std::endl;
		}
		return os;
	}
protected: // inheriting classes can access these constructors. External users can not
	Tag(const std::string& name, const std::string& text) : name(name), text(text) {}
	Tag(const std::string& name, const std::vector<Tag>& children) : name(name), children(children) {}
};

// single responsability: differenciate a tag into a HTML paragraph
struct P : public Tag {
	P(const std::string& text) : 
		Tag("p", text) // call the constructor of the base class
	{}

	P(std::initializer_list<Tag> children) :
		Tag("p", children)
	{}
};

struct IMG : public Tag {
	explicit IMG(const std::string& url) :
		Tag("img", "") // IMG is a tag without text in between
	{
		attributes.emplace_back(std::make_pair("src", url)); // but it has the url to the image as an attribute so we need to add this to the Tag (data management class with regard to single responsability principle)
	}
};

int main()
{
	std::cout << 
		P{
			IMG {"https://www.example.com/images/dinosaur.jpg"}, // this is only possible by defining the std::initializer_list<Tag> constructor on P
			IMG {"https://www.example.com/images/dinosaur2.jpg"}
		}
	<< std::endl;
	return 0;
}