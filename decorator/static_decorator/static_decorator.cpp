#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

// abstact base class
struct Shape {
	virtual std::string str() const = 0;
};

struct Circle : public Shape {
	float _radius;
	Circle() {}

	Circle(float rad) :
	_radius(rad) {}

	void resize(float scale) {
		_radius *= scale;
	}

	std::string str() const override {
		std::ostringstream oss;
		oss << "The circle has a radius of " << _radius;
		return oss.str();
	}	
};

struct Square : public Shape {
	float _side;

	Square() {}

	Square(float side) :
	_side(side) {}

	std::string str() const override {
		std::ostringstream oss;
		oss << "The Square has a side of " << _side;
		return oss.str();
	}
};

// C++ concept to restrict T to be a subtype of the Shape base class
template <typename T>
concept IsAShape = std::is_base_of<Shape, T>::value;

template <IsAShape T> 
struct ColoredShape2 : public T // minin inheritance
{
	std::string _color;

	ColoredShape2() {}

	// perfect forwarding constructor 
	template<typename...Args>
	ColoredShape2(const std::string& color, Args ...args) :
	T(std::forward<Args>(args)...),
	_color{color} 
	{}

	std::string str() const override {
		std::ostringstream oss;
		oss << T::str() << " has the color " << _color;
		return oss.str();
	}
};

// second decorator
template <IsAShape T> 
struct TransparentShape2 : public T // minin inheritance
{
	uint8_t _transparency;

	TransparentShape2() {}

	// perfect forwarding constructor 
	template<typename...Args>
	TransparentShape2(const uint8_t transp, Args ...args) :
	T(std::forward<Args>(args)...),
	_transparency{transp} 
	{}

	std::string str() const override {
		std::ostringstream oss;
		oss << T::str() << " has the transparancy " << static_cast<float>(_transparency) / 255.f * 100.f;
		return oss.str();
	}
};


int main()
{
	ColoredShape2<Circle> redCircle("red", 42); // in contrast to the previous example, the colored shape is a differenciation of Cicle via the template argument
		// therefore we can call the methods of the Circle class from the Decorator class
	redCircle.resize(1.5);
	std::cout << redCircle.str() << std::endl;


	// more then one decorator
	TransparentShape2<ColoredShape2<Circle>> redTranspCircle(42, "red", 42); // in contrast to the previous example, the colored shape is a differenciation of Cicle via the template argument
		// therefore we can call the methods of the Circle class from the Decorator class
	redTranspCircle._color += "light"; // access to the members that inherit from the Shape base class
	std::cout << redTranspCircle.str() << std::endl;

	return 0;
}