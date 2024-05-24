#include "Point.h"

Point::Point(double x, double y)
{
	X = x;
	Y = y;
}

std::ostream& operator<<(std::ostream& str, const Point& v)
{
	return str << "(" << v.X << ", " << v.Y << ")";
}