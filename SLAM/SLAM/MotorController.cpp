//
// File: MotorController.cpp
// Author: Kevin Fox
// Implementation for MotorController class
//

#include "pch.h"
#include "MotorController.h"
#include "GpioDefs.h"
#include "Motor.h"

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

void MotorController::goForward(Motor ^motorRight, Motor ^motorLeft)
{
	//currDirection = forward;
	return;
}

void MotorController::goLeft(Motor ^motorRight, Motor ^motorLeft)
{
	//currDirection = left;
	return;
}

void MotorController::goRight(Motor ^motorRight, Motor ^motorLeft)
{
	//currDirection = right;
	return;
}

void MotorController::goIdle(Motor ^motorRight, Motor ^motorLeft)
{
	//currDirection = idle;
	return;
}

void MotorController::goBrake(Motor ^motorRight, Motor ^motorLeft)
{
	//currDirection = brake;
	return;
}
void MotorController::goRotRight(Motor ^motorRight, Motor ^motorLeft)
{
	//currDirection = rotRight;
	return;
}

void MotorController::goRotLeft(Motor ^motorRight, Motor ^motorLeft)
{
	
	//currDirection = rotLeft;
	return;
}

void MotorController::goReverse(Motor ^motorRight, Motor ^motorLeft)
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
