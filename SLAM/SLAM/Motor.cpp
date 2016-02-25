//
// File: Motor.cpp
// Author: Kevin Fox
// Implementation for Motor class
//

#include "pch.h"
#include "Motor.h"
#include "GpioDefs.h"

/*
class Motor
{
public:
Motor(const int pwnPinNum, PwmController ^pwmController, double dutyCycle, GpioController ^gpio, const int inA, const int inB, const int enA, const int enB);
Motor(); //default constructor
void setDutyCycle(double dutyCycle, PwmController ^pwm);
double getDutyCycle();
void setPWMPin(const int inPwm, PwmController ^pwmController);
void setINAPin(const int inINA, GpioController ^gpio);
void setINBPin(const int inINB, GpioController ^gpio);
void setENAPin(const int inENA, GpioController ^gpio);
void setENBPin(const int inENB, GpioController ^gpio);
void writeINA(GpioPinValue value);
void writeINB(GpioPinValue value);
void writeENA(GpioPinValue value);
void writeENB(GpioPinValue value);

private:
double currDutyCycle;
PwmPin ^pwm;
GpioPin ^INA;
GpioPin ^INB;
GpioPin ^ENA;
GpioPin ^ENB;

};
*/

Motor::Motor(const int pwnPinNum, PwmController ^pwmController, double dutyCycle, GpioController ^gpio, const int inA, const int inB, const int enA, const int enB)
{
	return;
}

Motor::Motor() //default constructor
{
	return;
}

void setDutyCycle(double dutyCycle, PwmController ^pwm)
{
	return;
}

double getDutyCycle()
{
	return;
}

void setPWMPin(const int inPwm, PwmController ^pwmController)
{
	return;
}

void setINAPin(const int inINA, GpioController ^gpio)
{
	return;
}

void setINBPin(const int inINB, GpioController ^gpio)
{
	return;
}

void setENAPin(const int inENA, GpioController ^gpio)
{
	return;
}

void setENBPin(const int inENB, GpioController ^gpio)
{
	return;
}

void writeINA(GpioPinValue value)
{
	return;
}

void writeINB(GpioPinValue value)
{
	return;
}

void writeENA(GpioPinValue value)
{
	return;
}

void writeENB(GpioPinValue value)
{
	return;
}