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


struct ColoredShape : public Shape {
	Shape& _shape;
	std::string _color;

	ColoredShape(Shape& shape, const std::string& color) :
	_shape(shape),
	_color(color) {}


	std::string str() const override {
		std::ostringstream oss;
		oss << _shape.str() << " has the color " << _color;
		return oss.str();
	}
};

struct TransparentShape : public Shape {
	Shape& _shape;
	uint8_t _transp;
	
	TransparentShape(Shape& shape, uint8_t transparency) :
	_shape(shape),
	_transp(transparency) {}

	std::string str() const override {
		std::ostringstream oss;
		oss << _shape.str() << " has transparency " << static_cast<float>(_transp) / 255.f * 100.f;
		return oss.str();
	}
};


int main()
{
	Square sq(5);
	ColoredShape coloredSq(sq, "blue");
	TransparentShape tansColSq(coloredSq, 112);
	std::cout << tansColSq.str() << std::endl;
	return 0;
}