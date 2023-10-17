#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Renderer
{
    virtual string what_to_render_as() const = 0;
};

struct RasterRenderer : public Renderer {
    string what_to_render_as() const override {
        std::string printStr{ "pixels" };
        return printStr;
    }
};

struct VectorRenderer : public Renderer {
    string what_to_render_as() const {
        std::string printStr{ "lines" };
        return printStr;
    }
};

struct Shape
{
    Shape(Renderer& renderer) : _renderer{ renderer } {}
    std::string str() {
        return "Drawing " + name + " as " + _renderer.what_to_render_as();
    }

    string name;
    Renderer& _renderer;
};

struct Triangle : Shape
{
    Triangle(Renderer& renderer) :
    Shape(renderer)
    {
        name = "Triangle";
    }
};

struct Square : Shape
{
    Square(Renderer& renderer) :
    Shape(renderer)
    {
        name = "Square";
    }
};

// the following lines need to get refactored away
/*
struct VectorSquare : Square
{
    string str() const
    {
        return "Drawing " + name + " as lines";
    }
};

struct RasterSquare : Square
{
    string str() const
    {
        return "Drawing " + name + " as pixels";
    }
};
*/
// imagine e.g. VectorTriangle/RasterTriangle etc. here


int main()
{
    RasterRenderer rr;
    Triangle triangle(rr);
    std::cout << triangle.str() << std::endl;
    //std::cout << Triangle(RasterRenderer()).str() << std::endl;

	return 0;
}