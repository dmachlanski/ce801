#pragma once
#ifndef MEMFUNC_H
#define MEMFUNC_H

#include "Point.h"
#include <vector>

using namespace std;

struct MembershipFunction
{
public:
	string Name;
	vector<Point> Points;

	MembershipFunction();
	MembershipFunction(string name);
	bool ContainsX(double x);
	double GetValue(double x);

private:
	Point _findStartingPoint(double x);
	Point _findEndingPoint(double x);
	double _getMinX();
	double _getMaxX();
};

#endif // !MEMFUNC_H