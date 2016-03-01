#pragma once

//
// File: MotorController.h
// Author: Kevin Fox
// Header file for MotorController class
//

//USING ENUM INSTEAD OF #define
/*
#define brake 0
#define forward 1
#define left 2
#define rotLeft 3
#define right 4
#define rotRight 5
#define reverse 6
*/

#include "Motor.h"

using namespace Windows::Devices::Pwm;
//enum MotorStatus { brake, idle, reverse, forward, left, rotLeft, right, rotRight};

class MotorController
{
	public:
		//enum MotorStatus { brake, idle, reverse, forward, left, rotLeft, right, rotRight };//don't need this if we use the go functions

		void goForward();
		void goLeft();
		void goRight();
		void goIdle();
		//void goBrake();
		void goRotRight();
		void goRotLeft();
		void goReverse();
		//MotorStatus getDir() const;
		MotorController(Motor *leftMotor, Motor *rightMotor); //default constructor
	private:
		Motor *motorLeft;
		Motor *motorRight;
		//MotorStatus currDirection;
};


//enum MotorStatus { brake, idle, reverse, forward, left, rotLeft, right, rotRight };//don't need this if we use the go functions


