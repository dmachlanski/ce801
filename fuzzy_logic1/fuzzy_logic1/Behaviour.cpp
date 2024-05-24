#include "Behaviour.h"

Behaviour::Behaviour()
{
	// Does nothing
}

array<double, 2> Behaviour::GetOutput(vector<double> input)
{
	// Expected number of outputs
	const int outCount = 2;
	array<double, outCount> result;
	double numerators[outCount] = { 0 };
	double denominators[outCount] = { 0 };

	// Get firings for each input
	vector<vector<FiringStrength>> firings;
	for (double x : input)
	{
		firings.push_back(FSet.GetFiringStrength(x));
	}

	// Get all combinations of firings
	auto combinations = _getCombinations(firings);

	for (auto c : combinations)
	{
		// Get output rules according to the rule table
		auto rules = GetRule(c);

		// Apply MIN to the combination of firings
		double min_value = _getMin(c);

		// Min value * centroid value of the rule
		// Divided by the min value
		for (int i = 0; i < rules.size(); i++)
		{
			numerators[i] += min_value * Centroids[rules[i]];
			denominators[i] += min_value;
		}
	}

	// Calculate the final output
	for (int i = 0; i < outCount; i++)
	{
		result[i] = denominators[i] != 0 ? numerators[i] / denominators[i] : 0;
	}

	return result;
}

vector<vector<FiringStrength>> Behaviour::_getCombinations(vector<vector<FiringStrength>> &input)
{
	vector<FiringStrength> tmp;
	size_t n = input.size();
	vector<vector<FiringStrength>> result;
	_permute(input, result, n, 0, tmp);

	return result;
}

void Behaviour::_permute(vector<vector<FiringStrength>>& input, vector<vector<FiringStrength>>& output, size_t width, size_t row, vector<FiringStrength>& tmp)
{
	if (row < width)
	{
		for (int c = 0; c < input[row].size(); c++)
		{
			tmp.push_back(input[row][c]);
			_permute(input, output, width, row + 1, tmp);
			tmp.pop_back();
		}
	}
	else
	{
		output.push_back(tmp);
	}
}

double Behaviour::_getMin(vector<FiringStrength>& input)
{
	// Firings are expected to be within <0; 1> range
	double result = 2.0;
	for (auto fs : input)
	{
		if (fs.Strength < result)
		{
			result = fs.Strength;
		}
	}

	return result;
}
