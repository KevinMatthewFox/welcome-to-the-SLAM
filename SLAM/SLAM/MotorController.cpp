//
// File: MotorController.cpp
// Author: Kevin Fox
// Implementation for MotorController class
//

#include "pch.h"
#include "MotorController.h"

//CLASS DEFINITION
/*
class MotorController
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
		MotorController(); //default constructor
	private:
		MotorStatus currDirection;
};
*/

void MotorController::goForward(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	//currDirection = forward;
	return;
}

void MotorController::goLeft(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	//currDirection = left;
	return;
}

void MotorController::goRight(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	//currDirection = right;
	return;
}

void MotorController::goIdle(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	//currDirection = idle;
	return;
}

void MotorController::goBrake(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	//currDirection = brake;
	return;
}
void MotorController::goRotRight(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	//currDirection = rotRight;
	return;
}

void MotorController::goRotLeft(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	
	//currDirection = rotLeft;
	return;
}

void MotorController::goReverse(PwmPin ^motorOutput1, PwmPin ^motorOutput2)
{
	//currDirection = reverse;
	return;
}

MotorController::MotorController()
{
	//currDirection = idle;
	return;
}


/*
MotorStatus MotorController::getDir() const
{
	return currDirection;
}
*/