#include "BlendedControl.h"

BlendedControl::BlendedControl()
{
	string names[] = { "OA", "REF" };

	_mf_OA = MembershipFunction(names[0]);
	_mf_OA.Points.push_back(Point(0, 0));
	_mf_OA.Points.push_back(Point(190, 0));
	_mf_OA.Points.push_back(Point(191, 1));
	_mf_OA.Points.push_back(Point(300, 1));
	_mf_OA.Points.push_back(Point(600, 0));
	_mf_OA.Points.push_back(Point(6000, 0));

	_mf_REF = MembershipFunction(names[1]);
	_mf_REF.Points.push_back(Point(0, 0));
	_mf_REF.Points.push_back(Point(300, 0));
	_mf_REF.Points.push_back(Point(600, 1));
	_mf_REF.Points.push_back(Point(6000, 1));
}

array<double, 2> BlendedControl::GetOutput(vector<double> input)
{
	// Take the minimum of front readings
	double oa_min = min(min(input[0], input[1]), input[2]);
	
	// Get firing strengths based on minimum front reading
	double f_OA = _mf_OA.GetValue(oa_min);
	double f_REF = _mf_REF.GetValue(oa_min);
	
	// Get outputs for OA and REF behaviours
	auto speed_OA = _oa.GetOutput({ input[0], input[1], input[2] });
	auto speed_REF = _ref.GetOutput({ input[3], input[4] });

	// Calculate wheels speed (safe divide to avoid zero division problem)
	double final_LSpeed = ((f_REF * speed_REF[0]) + (f_OA * speed_OA[0])) / (f_REF + f_OA + 0.00001);
	double final_RSpeed = ((f_REF * speed_REF[1]) + (f_OA * speed_OA[1])) / (f_REF + f_OA + 0.00001);

	array<double, 2> result = { final_LSpeed, final_RSpeed };
	return result;
}
