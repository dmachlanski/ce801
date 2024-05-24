#pragma once
#ifndef OA_H
#define OA_H

#include "Behaviour.h"

class ObstacleAvoidance : public Behaviour
{
public:
	ObstacleAvoidance();

protected:
	vector<string> GetRule(vector<FiringStrength> input) override;
};

#endif // !OA_H