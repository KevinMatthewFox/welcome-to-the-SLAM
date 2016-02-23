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
		void setDir(MotorStatus);
		MotorStatus getDir() const;
	private:
		MotorStatus status;
};

enum MotorStatus { brake, idle, reverse, forward, left, rotLeft, right, rotRight};
*/

/*
Motor::Motor()
{
	this->status = idle;
	return;
}

void Motor::setDir(MotorStatus dir)
{
	this->status = dir;
	if (dir == brake)
	{
		//set brake
	}
	else if (dir == idle)
	{
		//both motors off
	}
	else if (dir == reverse)
	{
		//both motors reverse
	}
	else if (dir == forward)
	{
		//both motors forward
	}
	else if (dir == left)
	{
		//right motor forward, left motor off
	}
	else if (dir == rotLeft)
	{
		//right motor forward, left motor reverse
	}
	else if (dir == right)
	{
		//right motor off, left motor forward
	}
	else if (dir == rotRight)
	{
		//right motor reverse, left motor forward
	}
	else
	{
		status = idle;
		//idle
	}
	return;
}

MotorStatus Motor::getDir() const
{
	return status;
}
*/