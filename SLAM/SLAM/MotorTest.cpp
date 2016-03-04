//
// File: MotorTest.cpp
// Author: Kevin Fox
//

#include "pch.h"
#include "MotorTest.h"
#include "GpioDefs.h"

void motorTest(MotorController *motorController, GpioPin ^inputTransmitter)
{
	int state = 0;
	bool justRead = false;
	while (1)
	{
		if ((justRead == false) && (inputTransmitter->Read() == HIGH))
		{
			switch (state)
			{
			case 0:
				state = 1;
				justRead = true;
				motorController->goForward();
				break;
			case 1:
				state = 2;
				justRead = true;
				motorController->goIdle();
				break;
			case 2:
				state = 3;
				justRead = true;
				motorController->goReverse();
				break;
			case 3:
				state = 4;
				justRead = true;
				motorController->goRight();
				break;
			case 4:
				state = 5;
				justRead = true;
				motorController->goLeft();
				break;
			case 5:
				state = 6;
				justRead = true;
				motorController->goRotRight();
				break;
			case 6:
				state = 0;
				justRead = true;
				motorController->goRotLeft();
				break;
			default:
				state = 0;
				justRead = true;
				motorController->goForward();
				break;
			}
		}
		else
		{
			justRead = false;
		}
	}
}
