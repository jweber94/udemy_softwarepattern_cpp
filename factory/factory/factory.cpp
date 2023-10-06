#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


using namespace std;
using namespace boost;

enum class PointType {
	cartesian,
	polar
};

/* Separation of concerns/single responsability principle: Storing data and manage it */
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
		friend class PointFactory;

		friend std::ostream& operator << (std::ostream& os, Point p) {
			os << "x = " << p._x << "; y = " << p._y;
			return os;
		}
};


/* Separation of concerns/single responsability principle: Creating instances of Point with dedicated APIs */
class PointFactory {
	public:
		/* Factory Methods */
		static Point NewCartesian(float x, float y) {
			return Point(x, y);
		}

		static Point NewPolar(float r, float theta) {
			return {r*cos(theta), r*sin(theta)}; // implicit call to the constructor
		}
};

int main()
{
	Point myPoint1 = PointFactory::NewCartesian(5, 6);
	Point myPoint2 = PointFactory::NewPolar(2, M_PI/2);
	// Point myPoint3 = Point(3, 5); // does not work because we made the constructor private to enforce the use of the factory methods
	std::cout << "myPoint1 is " << myPoint1 << " and myPoint2 is " << myPoint2 << std::endl;
	return 0;
}