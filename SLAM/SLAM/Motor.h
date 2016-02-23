#pragma once

//
// File: Motor.h
// Author: Kevin Fox
// Header file for Motor class
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

using namespace Windows::Devices::Gpio;

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

enum MotorStatus { brake, idle, reverse, forward, left, rotLeft, right, rotRight};//don't need this if we use the go functions


