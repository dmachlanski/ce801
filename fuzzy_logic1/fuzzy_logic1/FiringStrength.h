#pragma once
#ifndef FIRINGSTRENGTH_H
#define FIRINGSTRENGTH_H

#include <string>

struct FiringStrength
{
public:
	std::string Name;
	double Strength;

	FiringStrength(std::string name, double strength);
	friend std::ostream& operator<<(std::ostream & str, const FiringStrength& v);
};

#endif // !FIRINGSTRENGTH_H