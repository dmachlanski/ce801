#include "Subsumption.h"

Subsumption::Subsumption(int threshold)
{
	_behaviourThreshold = threshold;
}

array<double, 2> Subsumption::GetOutput(vector<double> input)
{
	// input0 - sonar2
	// input1 - min(sonar3, sonar4)
	// input2 - sonar5
	// input3 - sonar6
	// input4 - sonar7

	array<double, 2> result;

	// If the minimum reading of front sensors is lower than defined threshold
	// then use OA; REF otherwise.
	if (min(min(input[0], input[1]), input[2]) < _behaviourThreshold)
	{
		result = _oa.GetOutput({ input[0], input[1], input[2] });
	}
	else
	{
		result = _ref.GetOutput({ input[3], input[4] });
	}

	return result;
}
