#pragma once
#ifndef BLENDEDCONTROL_H
#define BLENDEDCONTROL_H

#include "ObstacleAvoidance.h"
#include "RightEdgeFollowing.h"

class BlendedControl
{
public:
	BlendedControl();
	array<double, 2> GetOutput(vector<double> input);

private:
	ObstacleAvoidance _oa;
	RightEdgeFollowing _ref;
	MembershipFunction _mf_REF, _mf_OA;
};

#endif // !BLENDEDCONTROL_H