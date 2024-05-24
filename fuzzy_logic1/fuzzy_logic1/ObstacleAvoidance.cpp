#include "ObstacleAvoidance.h"

ObstacleAvoidance::ObstacleAvoidance()
{
	string names[] = { "L", "M", "H" };

	//** LXX **
	// LLX
	Rules.insert(pair<string, vector<string>>("LLL", { "L", "H" }));
	Rules.insert(pair<string, vector<string>>("LLM", { "L", "H" }));
	Rules.insert(pair<string, vector<string>>("LLH", { "H", "L" }));
	// LMX
	Rules.insert(pair<string, vector<string>>("LML", { "L", "H" }));
	Rules.insert(pair<string, vector<string>>("LMM", { "L", "H" }));
	Rules.insert(pair<string, vector<string>>("LMH", { "H", "L" }));
	// LHX
	Rules.insert(pair<string, vector<string>>("LHL", { "M", "M" }));
	Rules.insert(pair<string, vector<string>>("LHM", { "M", "M" }));
	Rules.insert(pair<string, vector<string>>("LHH", { "H", "M" }));

	//** MXX **
	// MLX
	Rules.insert(pair<string, vector<string>>("MLL", { "L", "H" }));
	Rules.insert(pair<string, vector<string>>("MLM", { "L", "H" }));
	Rules.insert(pair<string, vector<string>>("MLH", { "H", "L" }));
	// MMX
	Rules.insert(pair<string, vector<string>>("MML", { "M", "H" }));
	Rules.insert(pair<string, vector<string>>("MMM", { "M", "H" }));
	Rules.insert(pair<string, vector<string>>("MMH", { "H", "M" }));
	// MHX
	Rules.insert(pair<string, vector<string>>("MHL", { "M", "H" }));
	Rules.insert(pair<string, vector<string>>("MHM", { "M", "M" }));
	Rules.insert(pair<string, vector<string>>("MHH", { "H", "M" }));

	//** HXX **
	// HLX
	Rules.insert(pair<string, vector<string>>("HLL", { "L", "H" }));
	Rules.insert(pair<string, vector<string>>("HLM", { "L", "H" }));
	Rules.insert(pair<string, vector<string>>("HLH", { "L", "H" }));
	// HMX
	Rules.insert(pair<string, vector<string>>("HML", { "M", "H" }));
	Rules.insert(pair<string, vector<string>>("HMM", { "M", "H" }));
	Rules.insert(pair<string, vector<string>>("HMH", { "M", "H" }));
	// HHX
	Rules.insert(pair<string, vector<string>>("HHL", { "M", "H" }));
	Rules.insert(pair<string, vector<string>>("HHM", { "M", "H" }));
	Rules.insert(pair<string, vector<string>>("HHH", { "M", "M" }));

	MembershipFunction func1(names[0]);
	func1.Points.push_back(Point(0, 1));
	func1.Points.push_back(Point(150, 1));
	func1.Points.push_back(Point(370, 0));

	MembershipFunction func2(names[1]);
	func2.Points.push_back(Point(130, 0));
	func2.Points.push_back(Point(350, 1));
	func2.Points.push_back(Point(500, 1));
	func2.Points.push_back(Point(725, 0));

	MembershipFunction func3(names[2]);
	func3.Points.push_back(Point(485, 0));
	func3.Points.push_back(Point(700, 1));
	func3.Points.push_back(Point(5000, 1));

	Behaviour::FSet.Functions.push_back(func1);
	Behaviour::FSet.Functions.push_back(func2);
	Behaviour::FSet.Functions.push_back(func3);

	Behaviour::Centroids.insert(pair<string, double>(names[0], 50));
	Behaviour::Centroids.insert(pair<string, double>(names[1], 150));
	Behaviour::Centroids.insert(pair<string, double>(names[2], 350));
}

vector<string> ObstacleAvoidance::GetRule(vector<FiringStrength> input)
{
	string inputs = input[0].Name + input[1].Name + input[2].Name;

	return Rules[inputs];
}