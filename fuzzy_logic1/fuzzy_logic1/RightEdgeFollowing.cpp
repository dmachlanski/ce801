#include "RightEdgeFollowing.h"

RightEdgeFollowing::RightEdgeFollowing()
{
	string names[] = { "L", "M", "H" };
	
	Rules.insert(pair<string, vector<string>>("LL", {"L", "H"}));
	Rules.insert(pair<string, vector<string>>("LM", {"L", "H"}));
	Rules.insert(pair<string, vector<string>>("LH", {"L", "H"}));

	Rules.insert(pair<string, vector<string>>("ML", {"M", "H"}));
	Rules.insert(pair<string, vector<string>>("MM", {"M", "M"}));
	Rules.insert(pair<string, vector<string>>("MH", {"M", "M"}));

	Rules.insert(pair<string, vector<string>>("HL", {"M", "H"}));
	Rules.insert(pair<string, vector<string>>("HM", {"M", "M"}));
	Rules.insert(pair<string, vector<string>>("HH", {"H", "L"}));

	MembershipFunction func1(names[0]);
	func1.Points.push_back(Point(0, 1));
	func1.Points.push_back(Point(250, 1));
	func1.Points.push_back(Point(365, 0));

	MembershipFunction func2(names[1]);
	func2.Points.push_back(Point(270, 0));
	func2.Points.push_back(Point(450, 1));
	func2.Points.push_back(Point(660, 0));

	MembershipFunction func3(names[2]);
	func3.Points.push_back(Point(565, 0));
	func3.Points.push_back(Point(700, 1));
	func3.Points.push_back(Point(5000, 1));

	Behaviour::FSet.Functions.push_back(func1);
	Behaviour::FSet.Functions.push_back(func2);
	Behaviour::FSet.Functions.push_back(func3);

	Behaviour::Centroids.insert(pair<string, double>(names[0], 50));
	Behaviour::Centroids.insert(pair<string, double>(names[1], 150));
	Behaviour::Centroids.insert(pair<string, double>(names[2], 280));
}

vector<string> RightEdgeFollowing::GetRule(vector<FiringStrength> input)
{
	string inputs = input[0].Name + input[1].Name;

	return Rules[inputs];
}