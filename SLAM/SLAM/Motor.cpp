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

void Motor::goForward(PwmPin ^motorOutputPin)
{
	return;
}

void Motor::goLeft(PwmPin ^motorOutputPin)
{
	return;
}

void Motor::goRight(PwmPin ^motorOutputPin)
{
	return;
}

void Motor::goIdle(PwmPin ^motorOutputPin)
{
	return;
}

void Motor::goBrake(PwmPin ^motorOutputPin)
{
	return;
}
void Motor::goRotRight(PwmPin ^motorOutputPin)
{
	return;
}

void Motor::goRotLeft(PwmPin ^motorOutputPin)
{
	return;
}

void Motor::goReverse(PwmPin ^motorOutputPin)
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