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

using namespace Windows::Devices::Pwm;
//enum MotorStatus { brake, idle, reverse, forward, left, rotLeft, right, rotRight};

class MotorController
{
	public:
		//enum MotorStatus { brake, idle, reverse, forward, left, rotLeft, right, rotRight };//don't need this if we use the go functions

		void goForward(Motor ^motorOutput1, Motor ^motorOutput2);
		void goLeft(PwmPin ^motorOutput1, PwmPin ^motorOutput2);
		void goRight(PwmPin ^motorOutput1, PwmPin ^motorOutput2);
		void goIdle(PwmPin ^motorOutput1, PwmPin ^motorOutput2);
		void goBrake(PwmPin ^motorOutput1, PwmPin ^motorOutput2);
		void goRotRight(PwmPin ^motorOutput1, PwmPin ^motorOutput2);
		void goRotLeft(PwmPin ^motorOutput1, PwmPin ^motorOutput2);
		void goReverse(PwmPin ^motorOutput1, PwmPin ^motorOutput2);
		//MotorStatus getDir() const;
		MotorController(); //default constructor
	private:
		//MotorStatus currDirection;
};


//enum MotorStatus { brake, idle, reverse, forward, left, rotLeft, right, rotRight };//don't need this if we use the go functions

