#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct Flower
{
    virtual std::string str() const = 0;
};

struct Rose : Flower
{
    std::string str() const override {
        std::ostringstream oss;
        oss << "A rose";
        return oss.str();
    }
};

struct RedFlower : Flower
{
    const Flower& _flower;
    std::string _color{ "red" };

    RedFlower(const Flower& flower) :
        _flower(flower)
    {
    }

    RedFlower(const RedFlower& obj) :
    _flower(obj._flower) // avoid adding the color two times by using the flower of the handed over flower
    {
    }
    
    std::string str() const override {
        std::ostringstream oss;
        std::string tmpStr = _flower.str();
        std::size_t posStart = _flower.str().find("that is");
        std::size_t posCol = _flower.str().find(_color);
        if (posStart != std::string::npos) { // check for already existing colors and then check if the color of this decorator already exists
            if (posCol == std::string::npos) {
                oss << _flower.str() << " and " << _color;
            }
            else {
                oss << _flower.str();
            }
        }
        else {
            oss << _flower.str() << " that is " << _color;
        }
        return oss.str();
    }
};

struct BlueFlower : Flower
{
    const Flower& _flower;
    std::string _color{ "blue" };

    BlueFlower(const Flower& flower) :
        _flower(flower)
    {
    }

    BlueFlower(const BlueFlower& obj) :
        _flower(obj._flower)
    {
    }

    std::string str() const override {
        std::ostringstream oss;
        std::string tmpStr = _flower.str();
        std::size_t posStart = _flower.str().find("that is");
        std::size_t posCol = _flower.str().find(_color);
        if (posStart != std::string::npos) { // check for already existing colors and then check if the color of this decorator already exists
            if (posCol == std::string::npos) {
                oss << _flower.str() << " and " << _color;
            }
            else {
                oss << _flower.str();
            }
        }
        else {
            oss << _flower.str() << " that is " << _color;
        }
        return oss.str();
    }
};

int main() {
    Rose rose;
    RedFlower red_rose{ rose };
    RedFlower red_red_rose{ red_rose };
    BlueFlower blue_red_rose{ red_rose };
    std::cout << rose.str() << std::endl;          // "A rose"
    std::cout << red_rose.str() << std::endl;      // "A rose that is red"
    std::cout << red_red_rose.str() << std::endl;  // "A rose that is red"
    std::cout << blue_red_rose.str() << std::endl; // "A rose that is red and blue"
    
    // additional tests
    RedFlower blue_red_red_rose{ blue_red_rose };
    std::cout << blue_red_red_rose.str() << std::endl;
    BlueFlower blue_blue_red_rose{ blue_red_rose };
    std::cout << blue_blue_red_rose.str() << std::endl;
    
    return 0;
}