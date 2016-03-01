//
// File: MotorController.cpp
// Author: Kevin Fox
// Implementation for MotorController class
//

#include "pch.h"
#include "MotorController.h"
#include "GpioDefs.h"
#include "Motor.h"

void MotorController::goForward()
{
	
	motorLeft->writeENA(HIGH);
	motorLeft->writeENB(HIGH);
	motorLeft->writeINA(HIGH);
	motorLeft->writeINB(LOW);

	motorRight->writeENA(HIGH);
	motorRight->writeENB(HIGH);
	motorRight->writeINA(HIGH);
	motorRight->writeINB(LOW);


	return;
}

void MotorController::goLeft()
{
	motorLeft->writeENA(LOW);
	motorLeft->writeENB(LOW);
	motorLeft->writeINA(LOW);
	motorLeft->writeINB(LOW);

	motorRight->writeENA(HIGH);
	motorRight->writeENB(HIGH);
	motorRight->writeINA(HIGH);
	motorRight->writeINB(LOW);

	return;
}

void MotorController::goRight()
{
	motorRight->writeENA(LOW);
	motorRight->writeENB(LOW);
	motorRight->writeINA(LOW);
	motorRight->writeINB(LOW);

	motorLeft->writeENA(HIGH);
	motorLeft->writeENB(HIGH);
	motorLeft->writeINA(HIGH);
	motorLeft->writeINB(LOW);

	return;
}

void MotorController::goIdle()
{
	motorLeft->writeENA(LOW);
	motorLeft->writeENB(LOW);
	motorLeft->writeINA(LOW);
	motorLeft->writeINB(LOW);

	motorRight->writeENA(LOW);
	motorRight->writeENB(LOW);
	motorRight->writeINA(LOW);
	motorRight->writeINB(LOW);

	return;
}

//void MotorController::goBrake()
//{
//	//currDirection = brake;
//	return;
//}

void MotorController::goRotRight()
{
	motorRight->writeENA(HIGH);                               //Right conterclockwise
	motorRight->writeENB(HIGH);
	motorRight->writeINA(LOW);
	motorRight->writeINB(HIGH);
	
	
	motorLeft->writeENA(HIGH);                                //Left clockwise
	motorLeft->writeENB(HIGH);
	motorLeft->writeINA(HIGH);
	motorLeft->writeINB(LOW);

	return;
}

void MotorController::goRotLeft()
{
	
	motorRight->writeENA(HIGH);                              //Right clockwise
	motorRight->writeENB(HIGH);
	motorRight->writeINA(HIGH);
	motorRight->writeINB(LOW);

	motorLeft->writeENA(HIGH);                               //Left conterclockwise
	motorLeft->writeENB(HIGH);
	motorLeft->writeINA(LOW);
	motorLeft->writeINB(HIGH);


	return;
}

void MotorController::goReverse()
{
	motorRight->writeENA(HIGH);                              //Right conterclockwise
	motorRight->writeENB(HIGH);
	motorRight->writeINA(LOW);
	motorRight->writeINB(HIGH);

	motorLeft->writeENA(HIGH);                               //Left conterclockwise
	motorLeft->writeENB(HIGH);
	motorLeft->writeINA(LOW);
	motorLeft->writeINB(HIGH);

	return;
}

MotorController::MotorController(Motor *leftMotor, Motor *rightMotor)
{
	//currDirection = idle;
	motorLeft = leftMotor;
	motorRight = rightMotor;
	return;
}


/*
MotorStatus MotorController::getDir() const
{
	return currDirection;
}
*/
