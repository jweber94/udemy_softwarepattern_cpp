#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>


using namespace std;
using namespace boost;

/* This is the API that we need to fulfill - aka the unchangeable, given API by a library that we want to use */
struct Point {
    int x;
    int y;

    // hash_value functuion as a friend of Point
    friend std::size_t hash_value(const Point& obj) {
        std::size_t seed = 0x1E44943F;
        boost::hash_combine(seed, obj.x);
        boost::hash_combine(seed, obj.y);
        return seed;
    }
};

void DrawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end) {
    // Here we want to print the points that we have handed over
    std::cout << "Start drawing" << std::endl;
    for (auto& i = start; i != end; ++i) {
        std::cout << "pixel x = " << i->x << "; y = " << i->y << std::endl;
    }
    std::cout << "Finished drawing" << std::endl;
}

/* This is the API of what we get from another library which we also cannot change or for that we want to implement the adapter to make it conform with the targeted API above */
struct Line {
    Point start;
    Point end;

    friend std::size_t hash_value(const Line& obj) {
        std::size_t seed = 0x4D274623;
        boost::hash_combine(seed, obj.start);
        boost::hash_combine(seed, obj.end);
        return seed;
    }
};

// base class in our own library that describes basic geometry information - base class e.g. for rectangles, triangles, ...
struct VectorObject {
    virtual std::vector<Line>::iterator begin();
    virtual std::vector<Line>::iterator end();
};


// concrete geometry implementation
struct VectorRectangle : public VectorObject {
    VectorRectangle(int x, int y, int width, int height) { // origin top left + width and height
        lines.emplace_back(Line{ Point{x, y}, Point{x + width, y} }); // top line
        lines.emplace_back(Line{ Point{x, y}, Point{x, y + height} }); // left line
        lines.emplace_back(Line{ Point{x, y + height}, Point{x + width, y + height} }); // bottom line
        lines.emplace_back(Line{ Point{x + width, y}, Point{x + width, y + height} }); // riight line

    }
    std::vector<Line> lines;
};

/* this is the actual adapter pattern */
struct LineToPointAdapterCaching {
    LineToPointAdapterCaching(Line& line) {
        // generating the hash
        boost::hash<Line> hash;     // create calculator for the Line (needs to have the hash_value method implemented)
        _line_hash = hash(line);    // calculate the actial hash based on the instance that is handed over to the adapter

        // check if this instance is already within the cache
        if (_cache.find(_line_hash) != _cache.end()) {
            // Line is already within the cache. Then we do not need to recalculate the points from the line. The _line_hash member is safed within the instance and we can access the already calculated data via this member and the static map
            return;
        }
        
        // calculation
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
                points.emplace_back(Point{ left, y });
            }
        }
        else if (0 == dx) { // horizontal line
            for (int x = left; x <= right; ++x) {
                points.emplace_back(Point{ x, top });
            }
        }
        else {
            std::cerr << "Normal lines are currently not implemented" << std::endl;
        }

        // add the calculated points vector to the cache
        _cache.insert({_line_hash, points});
    }

    virtual std::vector<Point>::iterator begin() {
        return _cache.at(_line_hash).begin();
    }

    virtual std::vector<Point>::iterator end() {
        return _cache.at(_line_hash).end();
    }

private:
    std::vector<Point> points;
    std::size_t _line_hash; // hash value of the line that is associatated with the concrete instance of the Point Line Adapter
    static std::unordered_map<std::size_t, std::vector<Point>> _cache; // std::unordered_map<hash value, calculated adapter values>

};

std::unordered_map<std::size_t, std::vector<Point>> LineToPointAdapterCaching::_cache{};


int main()
{
    std::vector<std::shared_ptr<VectorObject>> vectorObjects{
        std::make_shared<VectorRectangle>(10, 10, 100, 100),
        std::make_shared<VectorRectangle>(30, 30, 60, 60)
    };

    for (auto& o : vectorObjects) {
        for (auto& line : *o) {
            LineToPointAdapterCaching lpo{ line };
            DrawPoints(lpo.begin(), lpo.end());
        }
    }

    return 0;
}