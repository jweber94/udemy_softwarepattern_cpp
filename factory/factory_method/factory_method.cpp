#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <cmath>

using namespace std;
using namespace boost;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


enum class PointType {
	cartesian,
	polar
};

class Point 
{
	private:
		// internal storage uses the cartesian view of the coordinates
		float _x;
		float _y;

		Point(float x, float y) :
			_x(x),
			_y(y)
		{}

	public:
		/* Factory Methods */
		static Point NewCartesian(float x, float y) {
			return Point(x, y);
		}

		static Point NewPolar(float r, float theta) {
			return {r*cos(theta), r*sin(theta)}; // implicit call to the constructor
		}

		friend std::ostream& operator << (std::ostream& os, Point p) {
			os << "x = " << p._x << "; y = " << p._y;
			return os;
		}
};

int main()
{
	Point myPoint1 = Point::NewCartesian(5, 6);
	Point myPoint2 = Point::NewPolar(2, M_PI/2);
	// Point myPoint3 = Point(3, 5); // does not work because we made the constructor private to enforce the use of the factory methods
	std::cout << "myPoint1 is " << myPoint1 << " and myPoint2 is " << myPoint2 << std::endl;
	return 0;
}