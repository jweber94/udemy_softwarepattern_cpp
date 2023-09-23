#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Rectangle {
	public:
		Rectangle() = delete;
		Rectangle(int width, int height) :
			_width(width),
			_height(height) {
			_isSquare = false;
		}

		int getHeight() const {
			return _height;
		}

		virtual void setHeight(int height) {
			_height = height;
		}

		int getWidth() const {
			return _width;
		}

		virtual void setWidth(int width) {
			_width = width;
		}

		int area() const {
			return _height * _width;
		}

		// without this, the liskov substitution principle is broken due to a broken setter mechanic
		bool isSquare() const {
			return _isSquare;
		}

	protected:
		int _width;
		int _height;
		bool _isSquare;
};


class Square : public Rectangle {
	public:
		Square(int size) : 
			Rectangle(size, size) {
			_isSquare = true;
		}

		void setHeight(int height) override {
			_height = _width = height;
		}

		void setWidth(int width) override {
			_width = _height = width;
		}

	protected:

};


/* Rectangle API */
void process(Rectangle& rec) {
	int targetHeight = 10;
	int w;
	// without this if-branching, the liskov substitution principle is broken due to a broken setter mechanic
	if (!rec.isSquare()) {
		w = rec.getWidth();
	}
	else {
		w = targetHeight;
	}
	rec.setHeight(targetHeight); // Setter mechanic is broken by using this with the square

	std::cout << "Expect the area to " << boost::lexical_cast<std::string>((w * 10))
		<< "; get actual are with: " << rec.area() << std::endl;
}


int main()
{
	Rectangle testRect(3, 4);
	Square testSquare(5);
	process(testRect);
	process(testSquare);

	return 0;
}