#include "FiringStrength.h"

FiringStrength::FiringStrength(std::string name, double strength)
{
	Name = name;
	Strength = strength;
}

std::ostream& operator<<(std::ostream & str, const FiringStrength& v)
{
	str << "Name: " << v.Name << ", Strength: " << v.Strength;
	return str;
}