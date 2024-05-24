#pragma once
#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
public:
	double X;
	double Y;

	Point(double x, double y);
	friend std::ostream& operator<<(std::ostream& str, const Point& v);
};

#endif // !POINT_H