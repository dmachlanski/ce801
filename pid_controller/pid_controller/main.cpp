#include "Aria.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <deque>
#include <queue>

using namespace std;

// Gets the minimum of the numbers in the collection.
int getMinReading(deque<int> buffer)
{
	// Max sensor reading is 5000, so this is okay
	int result = 6000;

	deque<int>::iterator it = buffer.begin();
	while (it != buffer.end())
	{
		if (*it < result)
		{
			result = *it;
		}
		*it++;
	}

	return result;
}

// Get the average of numbers in the collection.
double getAverageReading(deque<int> buffer)
{
	double sum = 0;
	double div = double(buffer.size());
	
	deque<int>::iterator it = buffer.begin();
	while (it != buffer.end())
	{
		sum += *it;
		*it++;
	}

	return sum / div;
}

int main(int argc, char **argv)
{
	// Initialisations
	Aria::init();
	ArRobot robot;
	ArSensorReading *sonarSensor[8];

	ArArgumentParser argParser(&argc, argv);
	argParser.loadDefaultArguments();

	// Connect to robot (and laser, etc)
	ArRobotConnector robotConnector(&argParser, &robot);
	if (robotConnector.connectRobot())
	{
		std::cout << "Robot connected!" << std::endl;
	}

	robot.runAsync(false);
	robot.lock();
	robot.enableMotors();
	robot.unlock();

	// Safe start
	robot.setVel2(0, 0);
	
	// The value of cos(40) to adjust sensor readings
	const double cos40 = 0.766;

	// Desired distance from the wall
	const double wall_distance = 450;

	// The margin from desired wall distance that is taken into account when using readings.
	// This is to prevent numbers from being too small or too high, making calculations and
	// robot behaviour more stable.
	const double wall_distance_margin = 200;

	// Upper allowed bound for sensor readings
	const double max_current_distance = wall_distance + wall_distance_margin;

	// Lower allowed bound for sensor readings
	const double min_current_distance = wall_distance - wall_distance_margin;

	// The base wheel speed
	const double base_speed = 150;

	// Max difference allowed between readings
	const double max_diff = 500;
	
	// P constant of the controller
	const double kp = 0.5;

	// I constant of the controller
	const double ki = 0.01;

	// D constant of the controller
	const double kd = 0.4;

	// Error values
	double ep = 0, ep_prev = 0, ei = 0, ed = 0;
	
	// The amount of past readings to keep
	int sonar_buffer_size = 3;

	// Collections of past sonar readings
	std::deque<int> buffered_sonar6;
	std::deque<int> buffered_sonar7;

	// The amount of past Ei errors to keep
	int ei_buffer_size = 10;

	// Collection of past Ei errors
	std::queue<double> buffered_ei;

	// Diagnostics - dump sensor readings to a file
	//ofstream file;
	//file.open("data.csv", std::ios_base::app);

	while (true)
	{
		// Run (main logic)
		int sonarRange[8];
		for (int i = 0; i < 8; i++)
		{
			sonarSensor[i] = robot.getSonarReading(i);
			sonarRange[i] = sonarSensor[i]->getRange();
		}

		// Diagnostics
		//file << sonarRange[6] << "," << sonarRange[7] << endl;

		// Insert new readings into collections
		// Take into account sensors orientation
		buffered_sonar6.push_back(double(sonarRange[6]) * cos40);
		buffered_sonar7.push_back(sonarRange[7]);

		// Remove the oldest readings if exceeded desired buffer size
		if(int(buffered_sonar6.size()) > sonar_buffer_size)
		{
			buffered_sonar6.pop_front();
		}
		if(int(buffered_sonar7.size()) > sonar_buffer_size)
		{
			buffered_sonar7.pop_front();
		}

		// Get average readings based on all readings stored
		int sonar6 = getAverageReading(buffered_sonar6);
		int sonar7 = getAverageReading(buffered_sonar7);
		
		double current_distance;

		if(sonar6 < 5000 && sonar7 < 5000)
		{
			// Both sonars return sensible values
			if(abs(sonar6 - sonar7) > max_diff)
			{
				// But they are too different, so take the smallest one
				current_distance = min(sonar6, sonar7);
			}
			else
			{
				// Acceptable difference - take the average of both readings
				current_distance = (sonar6 + sonar7) / 2.0;
			}
		}
		else
		{
			// At least one reading returns max value (5k), so take the smallest one if possible
			if(sonar6 < 5000)
			{
				current_distance = sonar6;
			}
			else
			{
				current_distance = sonar7;
			}
		}

		// Ensure current distance is within reasonable numbers to prevent errors from skyrocketing
		if(current_distance > max_current_distance)
		{
			current_distance = max_current_distance;
		}
		else if(current_distance < min_current_distance)
		{
			current_distance = min_current_distance;
		}
		
		// Calculate Ep error
		ep = wall_distance - current_distance;
		
		// Calculate Ei error
		// ei stores current sum of buffered_ei collection
		ei += ep;
		buffered_ei.push(ep);
		if(int(buffered_ei.size()) > ei_buffer_size)
		{
			ei -= buffered_ei.front();
			buffered_ei.pop();
		}
		
		// Calculate Ed error
		ed = ep - ep_prev;
		ep_prev = ep;

		// Calculate the output
		double output = (kp * ep) + (ki * ei) + (kd * ed);

		// Set wheel speeds
		// Left = constant speed
		// Right = base speed + output from calculations
		robot.setVel2(base_speed, base_speed + output);
		
		ArUtil::sleep(100);
	}

	// Termination
	robot.lock();
	robot.stop();
	robot.unlock();
	Aria::exit(0);
	return 0;
}
