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

void Motor::goForward(GpioPin ^motorOutputPin)
{
	return;
}

void Motor::goLeft(GpioPin ^motorOutputPin)
{
	return;
}

void Motor::goRight(GpioPin ^motorOutputPin)
{
	return;
}

void Motor::goIdle(GpioPin ^motorOutputPin)
{
	return;
}

void Motor::goBrake(GpioPin ^motorOutputPin)
{
	return;
}
void Motor::goRotRight(GpioPin ^motorOutputPin)
{
	return;
}

void Motor::goRotLeft(GpioPin ^motorOutputPin)
{
	return;
}

void Motor::goReverse(GpioPin ^motorOutputPin)
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