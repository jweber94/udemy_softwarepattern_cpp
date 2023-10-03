struct Point
{
  int x{ 0 }, y{ 0 };

  Point(){}

  Point(const Point& p) :
  x(p.x),
  y(p.y)
  {}
  
  Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line
{
  Point *start;
  Point *end;
  
  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
  }

  Line(const Line& line) :
  start(new Point(*line.start)),
  end(new Point(*line.end))
  {}

  ~Line()
  {
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
    return Line(*this);
  }
};

int main()
{
    Line prototypeLine(new Point(0, 0), new Point(0, 0));
    Line deepCopied = prototypeLine.deep_copy();
	return 0;
}