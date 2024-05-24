#pragma once
#ifndef REF_H
#define REF_H

#include "Behaviour.h"

class RightEdgeFollowing : public Behaviour
{
public:
	RightEdgeFollowing();

protected:
	vector<string> GetRule(vector<FiringStrength> input) override;
};

#endif // !REF_H