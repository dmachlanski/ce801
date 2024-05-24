#include "MembershipFunction.h"
#include <iostream>

MembershipFunction::MembershipFunction()
{
}

MembershipFunction::MembershipFunction(string name)
{
	Name = name;
}

bool MembershipFunction::ContainsX(double x)
{
	return x >= _getMinX() && x <= _getMaxX();
}

double MembershipFunction::GetValue(double x)
{
	//Needs at least two points, otherwise return 0
	if (Points.size() < 2 || !ContainsX(x))
	{
		return 0;
	}

	// Assumes points are entered in ascending order
	Point startP = _findStartingPoint(x);
	Point endP = _findEndingPoint(x);

	double result = -1;

	//What kind of line is it?
	if (endP.Y > startP.Y)
	{
		//Arising
		result = (x - startP.X) / (endP.X - startP.X);
	}
	else if (endP.Y < startP.Y)
	{
		//Falling
		result = (endP.X - x) / (endP.X - startP.X);
	}
	else
	{
		//Flat
		result = startP.Y;
	}

	return result;
}

Point MembershipFunction::_findStartingPoint(double x)
{
	Point result = Point(-1, -1);

	if (Points.empty())
	{
		return result;
	}

	for (int i = 0; i < Points.size(); i++)
	{
		if (x >= Points[i].X)
		{
			result = Points[i];
		}
		else
		{
			break;
		}
	}

	return result;
}

Point MembershipFunction::_findEndingPoint(double x)
{
	Point result = Point(-1, -1);

	if (Points.empty())
	{
		return result;
	}

	for (int i = Points.size() - 1; i >= 0; i--)
	{
		if (x <= Points[i].X)
		{
			result = Points[i];
		}
		else
		{
			break;
		}
	}

	return result;
}

double MembershipFunction::_getMinX()
{
	if (Points.empty())
	{
		return -1;
	}

	double minX = Points[0].X;
	for (int i = 1; i < Points.size(); i++)
	{
		if (Points[i].X < minX)
		{
			minX = Points[i].X;
		}
	}

	return minX;
}

double MembershipFunction::_getMaxX()
{
	if (Points.empty())
	{
		return -1;
	}

	double maxX = Points[0].X;
	for (int i = 1; i < Points.size(); i++)
	{
		if (Points[i].X > maxX)
		{
			maxX = Points[i].X;
		}
	}

	return maxX;
}
