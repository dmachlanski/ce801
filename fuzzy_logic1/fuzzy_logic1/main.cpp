#include "Aria.h"
#include <iostream>
#include <fstream>
#include <deque>
#include "ObstacleAvoidance.h"
#include "RightEdgeFollowing.h"
#include "Subsumption.h"
#include "BlendedControl.h"

using namespace std;

// Gets minimum value from a given collection
int getMinReading(deque<int> buffer)
{
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

	// Number of readings to keep
	int sonar_buffer_size = 1;

	// Collections for sonar readings
	deque<int> buffered_sonar2;
	deque<int> buffered_sonar3;
	deque<int> buffered_sonar4;
	deque<int> buffered_sonar5;
	deque<int> buffered_sonar6;
	deque<int> buffered_sonar7;

	// Cos(40) value for adjustment purposes
	const double cos40 = 0.766;

	// Mode:
	// - 1: Right edge following
	// - 2: Obstacle avoidance
	// - 3: Subsumption
	// - 4: Blended control
	int mode = 4;
	RightEdgeFollowing ref;
	ObstacleAvoidance oa;
	Subsumption subsumption(800);
	BlendedControl blended;

	// Diagnostics - dump readings to a file
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

		// Update readings
		buffered_sonar2.push_back(sonarRange[2]);
		buffered_sonar3.push_back(sonarRange[3]);
		buffered_sonar4.push_back(sonarRange[4]);
		buffered_sonar5.push_back(sonarRange[5]);
		buffered_sonar6.push_back(sonarRange[6]);
		buffered_sonar7.push_back(sonarRange[7]);

		// Remove the oldest reading if exceeded collection size
		if (int(buffered_sonar2.size()) > sonar_buffer_size)
		{
			buffered_sonar2.pop_front();
		}
		if (int(buffered_sonar3.size()) > sonar_buffer_size)
		{
			buffered_sonar3.pop_front();
		}
		if (int(buffered_sonar4.size()) > sonar_buffer_size)
		{
			buffered_sonar4.pop_front();
		}
		if (int(buffered_sonar5.size()) > sonar_buffer_size)
		{
			buffered_sonar5.pop_front();
		}
		if (int(buffered_sonar6.size()) > sonar_buffer_size)
		{
			buffered_sonar6.pop_front();
		}
		if (int(buffered_sonar7.size()) > sonar_buffer_size)
		{
			buffered_sonar7.pop_front();
		}

		// Get minimum readings
		double sonar2 = getMinReading(buffered_sonar2);
		double sonar3 = getMinReading(buffered_sonar3);
		double sonar4 = getMinReading(buffered_sonar4);
		double sonar5 = getMinReading(buffered_sonar5);
		double sonar6 = getMinReading(buffered_sonar6);
		double sonar7 = getMinReading(buffered_sonar7);

		// Diagnostics
		//file << sonar2 << "," << sonar3 << "," << sonar4 << "," << sonar5 << "," << sonar6 << "," << sonar7 << endl;

		// Take the minimum of two front sensors
		double sonar34 = min(sonar3, sonar4);

		// Takes into account sonars orientation
		sonar6 *= cos40;

		array<double, 2> output;

		switch (mode)
		{
		case 1:
			output = ref.GetOutput({ sonar6, sonar7 });
			break;;
		case 2:
			output = oa.GetOutput({ sonar2, sonar34, sonar5 });
			break;
		case 3:
			output = subsumption.GetOutput({ sonar2, sonar34, sonar5, sonar6, sonar7 });
			break;
		default:
			output = blended.GetOutput({ sonar2, sonar34, sonar5, sonar6, sonar7 });
			break;
		}
		
		// Set wheels speed
		robot.setVel2(output[0], output[1]);
		
		ArUtil::sleep(100);
	}

	// Termination
	robot.lock();
	robot.stop();
	robot.unlock();
	Aria::exit(0);
	return 0;
}
