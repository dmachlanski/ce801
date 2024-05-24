#pragma once
#ifndef SUBSUMPTION_H
#define SUBSUMPTION_H

#include "RightEdgeFollowing.h"
#include "ObstacleAvoidance.h"

class Subsumption
{
public:
	Subsumption(int threshold);
	array<double, 2> GetOutput(vector<double> input);

private:
	RightEdgeFollowing _ref;
	ObstacleAvoidance _oa;
	int _behaviourThreshold;
};

#endif // !SUBSUMPTION_H