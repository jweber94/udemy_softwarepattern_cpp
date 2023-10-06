#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

// forward declaration
struct HtmlBuilder;

// single responsability: modeling a HTML element
struct HtmlElement {
	// members
	std::string _name, _text;
	std::vector<HtmlElement> _elements;
	const std::size_t _indentation = 2; // indentation size
	// constructors
	HtmlElement() {}
	HtmlElement(const std::string& name, const std::string& text) :
		_text(text),
		_name(name)
	{}
	// methods
	std::string str(std::size_t indent = 0)  const { // C++ fasion to get a string from an instance
		std::ostringstream oss; // define output string buffer

		// create appropriate indent with indentation size _indentation
		std::string i(indent * _indentation, ' '); // https://cplusplus.com/reference/string/string/string/ fill constructor

		oss << i << "<" << _name << ">" << std::endl; // indentation and opening tag with linebreak
		if (_text.size() > 0) {
			oss << std::string(indent * (_indentation + 1), ' ') << _text << std::endl; // another indentation of the acutal content
		}

		// recursive call of all elements are added
		for (const auto& e : _elements) {
			oss << e.str(indent + 1);
		}

		// closing tag
		oss << i << "</" << _name << ">" << std::endl;
		return oss.str(); // get constructed string from stringstream
	}

	// hint to the user that he should use the builder instead of the instance
	static HtmlBuilder build(std::string rootName); // { // Caution: this does not forbid to create an instance of HtmlElement on its own
	//	return HtmlBuilder(rootName);
	//}

};

// single responsability: the HtmlBuilder is responsible to create a HtmlElement instance in the background and deliver an easy API for filling it up
struct HtmlBuilder {
	HtmlElement _root;

	HtmlBuilder(std::string rootName) {
		_root._name = rootName;
	}

	// fluent approach
	HtmlBuilder& addChild(std::string name, std::string text) {
		HtmlElement tmpChild(name, text);
		_root._elements.push_back(tmpChild);
		return *this;
	}
	/*
	// non fluent approach
	void addChild(std::string name, std::string text) {
		HtmlElement tmpChild(name, text);
		_root._elements.push_back(tmpChild);
	}
	*/

	std::string str() const {
		return _root.str();
	}

	// Make it possible to get an element back from the builder and therefor enable to call ::build("ul") on the HtmlElement and receive a HtmlElement back
	operator HtmlElement() const { // this defines the () operator of HtmlBuilder
		return _root;
	}
};

HtmlBuilder HtmlElement::build(std::string rootName) { // Caution: this does not forbid to create an instance of HtmlElement on its own
	return HtmlBuilder(rootName);
}

int main()
{
	// fluent construction
	HtmlBuilder htmlBuilder("ul"); // creation of the root node enforced
	htmlBuilder.addChild("li", "hello").addChild("li", "world");
	std::cout << htmlBuilder.str() << std::endl;
	
	// HtmlElement construction with builder
	HtmlBuilder builder2 = HtmlElement::build("ul").addChild("li", "Foo").addChild("li", "Bar");
	std::cout << builder2.str() << std::endl;
	
	// build() with HtmlElement as return type
	HtmlElement elem = HtmlElement::build("ul").addChild("li", "Hello World!");

	return 0;
}