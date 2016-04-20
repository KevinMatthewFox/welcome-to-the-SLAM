//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//
// Author: ENGR 498 - Team 15017
//		Kevin Fox, Jiaxiang Wang
// Description: SLAM, baby
//


#include <wiringPi.h>
#include <softPwm.h>
#include "motor.h"

void goForward()
{
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(27, HIGH);
	digitalWrite(1, LOW);

	digitalWrite(25, HIGH);
	digitalWrite(2, HIGH);
	digitalWrite(24, HIGH);
	digitalWrite(3, LOW);

}

void goLeft()
{
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(27, LOW);
	digitalWrite(1, LOW);

	digitalWrite(25, HIGH);
	digitalWrite(2, HIGH);
	digitalWrite(24, HIGH);
	digitalWrite(3, LOW);

	return;
}

void goRight()
{
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(27, HIGH);
	digitalWrite(1, LOW);

	digitalWrite(25, LOW);
	digitalWrite(2, LOW);
	digitalWrite(24, LOW);
	digitalWrite(3, LOW);
	
	return;
}

void goIdle()
{
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(27, LOW);
	digitalWrite(1, LOW);

	digitalWrite(25, LOW);
	digitalWrite(2, LOW);
	digitalWrite(24, LOW);
	digitalWrite(3, LOW);

	return;
}

void goRotRight()
{
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(27, HIGH);
	digitalWrite(1, LOW);

	digitalWrite(25, HIGH);
	digitalWrite(2, HIGH);
	digitalWrite(24, LOW);
	digitalWrite(3, HIGH);
	
	return;
}

void goRotLeft()
{
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(27, LOW);
	digitalWrite(1, HIGH);

	digitalWrite(25, HIGH);
	digitalWrite(2, HIGH);
	digitalWrite(24, HIGH);
	digitalWrite(3, LOW);

	return;
}

void goReverse()
{
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(27, LOW);
	digitalWrite(1, HIGH);

	digitalWrite(25, HIGH);
	digitalWrite(2, HIGH);
	digitalWrite(24, LOW);
	digitalWrite(3, HIGH);

	return;
}

