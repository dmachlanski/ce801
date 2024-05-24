#include "Aria.h"
#include <cstdio>

int main(int argc, char **argv)
{
	// Initialisations
	Aria::init();
	ArRobot robot;
	ArSensorReading *sonarSensor[8];
	double wall_distance = 600;
	double wall_buffer = 100;
	double wall_minus_buffer = wall_distance - wall_buffer;
	double wall_plus_buffer = wall_distance + wall_buffer;
	double normal_speed = 100;
	double turn_speed = 10;

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
	
	while (true)
	{
		// Run (main logic)
		int sonarRange[8];
		for(int i = 0; i < 8; i++)
		{
			sonarSensor[i] = robot.getSonarReading(i);
			sonarRange[i] = sonarSensor[i]->getRange();
		}

		double left = sonarRange[0];
		double b = sonarRange[1];
		double front_left = sonarRange[3];
		double front_right = sonarRange[4];

		//double sine = left / b;

		//std::cout << left << std::endl;
		//std::cout << sine << std::endl;

		if(left < wall_minus_buffer)
		{
			// turn right
			robot.setVel2(normal_speed, turn_speed);
		}
		else if (left > wall_plus_buffer)
		{
			// turn left
			robot.setVel2(turn_speed, normal_speed);
		}
		else
		{
			// straight
			robot.setVel2(normal_speed, normal_speed);
		}
		
		ArUtil::sleep(100);
	}
	
	// Termination
	robot.lock();
	robot.stop();
	robot.unlock();
	Aria::exit(0);
	return 0;
}
