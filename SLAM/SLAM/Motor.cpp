//
// File: Motor.cpp
// Author: Kevin Fox
// Implementation for Motor class
//

#include "pch.h"
#include "Motor.h"

//CLASS DEFINITION
/*
class Motor
{
	public:
		void goForward(GpioPin ^motorOutputPin);
		void goLeft(GpioPin ^motorOutputPin);
		void goRight(GpioPin ^motorOutputPin);
		void goIdle(GpioPin ^motorOutputPin);
		void goBrake(GpioPin ^motorOutputPin);
		void goRotRight(GpioPin ^motorOutputPin);	
		void goRotLeft(GpioPin ^motorOutputPin);
		void goReverse(GpioPin ^motorOutputPin);
		MotorStatus getDir() const;
		Motor(); //default constructor
	private:
		MotorStatus currDirection;
};
*/

void Motor::goForward(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	return;
}

void Motor::goLeft(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	return;
}

void Motor::goRight(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	return;
}

void Motor::goIdle(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	return;
}

void Motor::goBrake(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	return;
}
void Motor::goRotRight(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	return;
}

void Motor::goRotLeft(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	return;
}

void Motor::goReverse(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	return;
}

Motor::Motor()
{
	currDirection = idle;
	return;
}


MotorStatus Motor::getDir() const
{
	return currDirection;
}