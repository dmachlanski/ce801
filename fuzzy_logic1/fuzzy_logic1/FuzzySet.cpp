#include "FuzzySet.h"

FuzzySet::FuzzySet()
{
	// Does nothing
}

vector<FiringStrength> FuzzySet::GetFiringStrength(double x)
{
	vector<FiringStrength> results;
	for (int i = 0; i < Functions.size(); i++)
	{
		if (Functions[i].ContainsX(x))
		{
			double strength = Functions[i].GetValue(x);
			results.push_back(FiringStrength(Functions[i].Name, strength));
		}
	}

	return results;
}

vector<string> FuzzySet::GetFunctionNames()
{
	vector<string> result;

	for (int i = 0; i < Functions.size(); i++)
	{
		result.push_back(Functions[i].Name);
	}

	return result;
}
