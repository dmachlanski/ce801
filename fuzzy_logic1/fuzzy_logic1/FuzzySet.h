#ifndef FUZZYSET_H
#define FUZZYSET_H

#include "MembershipFunction.h"
#include "FiringStrength.h"

using namespace std;

struct FuzzySet
{
public:
	vector<MembershipFunction> Functions;

	FuzzySet();
	vector<FiringStrength> GetFiringStrength(double x);
	vector<string> GetFunctionNames();
};

#endif // !FUZZYSET_H