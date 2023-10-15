#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

/* This is the API that we need to fulfill - aka the unchangeable, given API by a library that we want to use */
struct Point {
    int x;
    int y;
};

void DrawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end) {
    // Here we want to print the points that we have handed over
    std::cout << "Start drawing" << std::endl;
    for (auto&  i = start; i != end; ++i) {
        std::cout << "pixel x = " << i->x << "; y = " << i->y << std::endl; 
    }
    std::cout << "Finished drawing" << std::endl;
}

/* This is the API of what we get from another library which we also cannot change or for that we want to implement the adapter to make it conform with the targeted API above */
struct Line {
    Point start;
    Point end;
};

// base class in our own library that describes basic geometry information - base class e.g. for rectangles, triangles, ...
struct VectorObject {
    virtual std::vector<Line>::iterator begin();
    virtual std::vector<Line>::iterator end();
};


// concrete geometry implementation
struct VectorRectangle : public VectorObject {
    VectorRectangle(int x, int y, int width, int height) { // origin top left + width and height
        lines.emplace_back(Line{Point{x, y}, Point{x + width, y}}); // top line
        lines.emplace_back(Line{Point{x, y}, Point{x, y+height}}); // left line
        lines.emplace_back(Line{Point{x, y + height}, Point{x + width, y + height}}); // bottom line
        lines.emplace_back(Line{Point{x + width, y}, Point{x + width, y + height}}); // riight line

    }
    std::vector<Line> lines;   
};

/* this is the actual adapter pattern */  
struct LineToPointAdapter {
    LineToPointAdapter(Line& line) {
        // here comes the recalculation part of the adapter (= this example is not just a remapping but a mathmatical recalculation from the given API to the targeted API)
        static int count = 0;
        std::cout << count++ << "Generating points for line (no caching)\n" << std::endl; 
    
        int left = min(line.start.x, line.end.x);
        int right = max(line.start.x, line.end.x);
        int top = min(line.start.y, line.end.y);
        int bottom = max(line.start.y, line.end.y);

        // we assume a normalized coordinate system
        int dx = right - left;
        int dy = line.end.y - line.start.y;
        // slope is defined as m = dy / dx

        // catch corner cases to avoid dividing or multipling by zero
        if (0 == dx) {
            // vertical line
            for (int y = top; y <= bottom; ++y) {
                points.emplace_back(Point{left, y});
            }
        } else if (0 == dx) { // horizontal line
            for (int x = left; x <= right; ++x) {
                points.emplace_back(Point{x, top});
            }
        } else {
            std::cerr << "Normal lines are currently not implemented" << std::endl;
        }
    
    }

    virtual std::vector<Point>::iterator begin() {
        return points.begin();
    }

    virtual std::vector<Point>::iterator end() {
        return points.end();
    }

    private:
        std::vector<Point> points;
};

int main()
{

    std::vector<std::shared_ptr<VectorObject>> vectorObjects {
        std::make_shared<VectorRectangle>(10, 10, 100, 100),
        std::make_shared<VectorRectangle>(30, 30, 60, 60)
    };

    for (auto& o : vectorObjects) {
        for (auto& line : *o) {
            LineToPointAdapter lpo {line};
            DrawPoints(lpo.begin(), lpo.end());
        }
    }

	return 0;
}