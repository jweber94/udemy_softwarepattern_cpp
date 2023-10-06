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
class HtmlElement {
private: // not needed since it is the default on a class definition
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
public:
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
	static HtmlBuilder create(std::string rootName);// { // Caution: this does not forbid to create an instance of HtmlElement on its own
	//	return HtmlBuilder(rootName);
	//}

	friend HtmlBuilder; // allow HtmlBuilder to access private members of HtmlElement
};

// single responsability: the HtmlBuilder is responsible to create a HtmlElement instance in the background and deliver an easy API for filling it up
class HtmlBuilder {
private:
	HtmlElement _root;

public:
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

	// make the root accessable after it is constructed by the builder
	HtmlElement build() {
		return _root;
	}

};

HtmlBuilder HtmlElement::create(std::string rootName) { // Caution: this does not forbid to create an instance of HtmlElement on its own
	return HtmlBuilder(rootName);
}

int main()
{
	// fluent construction
	HtmlBuilder htmlBuilder("ul"); // creation of the root node enforced
	htmlBuilder.addChild("li", "hello").addChild("li", "world");
	std::cout << htmlBuilder.str() << std::endl;
	
	// HtmlElement construction with builder
	HtmlBuilder builder2 = HtmlElement::create("ul").addChild("li", "Foo").addChild("li", "Bar");
	std::cout << builder2.str() << std::endl;
	
	// build() with HtmlElement as return type
	HtmlElement elem = HtmlElement::create("ul").addChild("li", "Hello World!");

	// not allowed - no constructor of HtmlElement is available so the user will check what methods he can use on the class (which needs to be static since we have no instance to operate on)
	// HtmlElement elem;

	return 0;
}