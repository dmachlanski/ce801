#pragma once
#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "FuzzySet.h"
#include <map>
#include <array>

class Behaviour
{
public:
	Behaviour();
	array<double, 2> GetOutput(vector<double> input);

protected:
	FuzzySet FSet;
	map<string, vector<string>> Rules;
	map<string, double> Centroids;
	virtual vector<string> GetRule(vector<FiringStrength> input) = 0;

private:
	vector<vector<FiringStrength>> _getCombinations(vector<vector<FiringStrength>> &input);
	void _permute(vector<vector<FiringStrength>> &input, vector<vector<FiringStrength>> &output, size_t width, size_t row, vector<FiringStrength> &tmp);
	double _getMin(vector<FiringStrength> &input);
};

#endif // !BEHAVIOUR_H