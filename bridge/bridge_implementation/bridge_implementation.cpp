#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

// we have different renderers that are formalized via the abstract Renderer base class
struct Renderer { // renderer is the abstraction for the brige
	virtual void render_circle(float x, float y, float diameter) = 0;
};

// here comes the implementations that should get inserted via the abstraction of the brige with dependency injection
struct VectorRenderer : public Renderer {
	void render_circle(float x, float y, float diameter) override {
		std::cout << "Vector Renderer with cirle at x = " << x << "; y = " << y << "; diameter = " << diameter << std::endl;
	}
};

struct RasterRenderer : public Renderer {
	void render_circle(float x, float y, float diameter) override {
		std::cout << "Raster Renderer with cirle at x = " << x << "; y = " << y << "; diameter = " << diameter << std::endl;
	}
};

// adapter class
struct Shape {
protected:
	Renderer& _renderer; // this is the actual bridge implementation with Shape and the reference to the renderer base class
	Shape(Renderer& renderer) : _renderer(renderer) {

	}

public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

// every class that inherits from Shape (which contains the bridge via the renderer reference)
struct Circle : Shape {
	Circle(Renderer& renderer, float x, float y, float dia) : 
	Shape(renderer),
	x{x},
	y{y},
	diameter{dia}
	{}

	void draw() override {
		_renderer.render_circle(x, y, diameter);
	}

	void resize(float factor) override {
		diameter *= factor;
	}

	float x;
	float y;
	float diameter;
};

int main()
{
	RasterRenderer rr;
	Circle raster_circle(rr, 5, 5, 5);
	raster_circle.draw();
	raster_circle.resize(5);
	raster_circle.draw();
	return 0;
}