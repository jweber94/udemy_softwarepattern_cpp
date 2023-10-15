#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;


struct Square
{
    int side{ 0 };


    explicit Square(const int side)
        : side(side)
    {
    }
};

struct Rectangle
{
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area() const
    {
        return width() * height();
    }
};

struct SquareToRectangleAdapter : Rectangle
{
    SquareToRectangleAdapter(const Square& square)
        : _square(square)
    {}
    // todo
    int width() const {
        return _square.side;
    }

    int height() const {
        return _square.side;
    }

private:
    const Square& _square;
};

/* Simulated target API */
void processRectangle(const Rectangle& rect) {
    std::cout << "Height = " << rect.height() << "; Width = " << rect.width() << "; Area = " << rect.area() << std::endl;
}

int main()
{
    // create a given instance
    Square testSquare(5);

    // create adapter instance
    SquareToRectangleAdapter testAdapter(testSquare);

    // use the adapter with the target API
    processRectangle(testAdapter);

    return 0;
}
