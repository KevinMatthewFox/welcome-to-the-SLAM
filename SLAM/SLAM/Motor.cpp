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
GpioPin ^inA;
GpioPin ^inB;
GpioPin ^enA;
GpioPin ^enB;

};
*/

Motor::Motor(const int pwnPinNum, PwmController ^pwmController, double dutyCycle, GpioController ^gpio, const int inAPin, const int inBPin, const int enAPin, const int enBPin)
{
	currDutyCycle = dutyCycle;
	pwm = nullptr;
	pwm = pwmController->OpenPin(pwnPinNum);
	pwm->SetActiveDutyCyclePercentage(currDutyCycle);
	inA = nullptr;
	inB = nullptr;
	enA = nullptr;
	enB = nullptr;
	inA = gpio->OpenPin(inAPin);
	inB = gpio->OpenPin(inBPin);
	enA = gpio->OpenPin(enAPin);
	enB = gpio->OpenPin(enBPin);
	inA->SetDriveMode(OUTPUT);
	inB->SetDriveMode(OUTPUT);
	enA->SetDriveMode(OUTPUT);
	enB->SetDriveMode(OUTPUT);

	return;
}

Motor::Motor() //default constructor
{
	pwm = nullptr;
	inA = nullptr;
	inB = nullptr;
	enA = nullptr;
	enB = nullptr;
	return;
}

void Motor::setDutyCycle(double dutyCycle)
{
	currDutyCycle = dutyCycle;
	pwm->SetActiveDutyCyclePercentage(currDutyCycle);
	return;
}

double Motor::getDutyCycle()
{
	return;
}

void Motor::setPWMPin(const int inPwm, PwmController ^pwmController)
{
	return;
}

void Motor::setINAPin(const int inINA, GpioController ^gpio)
{
	return;
}

void Motor::setINBPin(const int inINB, GpioController ^gpio)
{
	return;
}

void Motor::setENAPin(const int inENA, GpioController ^gpio)
{
	return;
}

void Motor::setENBPin(const int inENB, GpioController ^gpio)
{
	return;
}

void Motor::writeINA(GpioPinValue value)
{
	return;
}

void Motor::writeINB(GpioPinValue value)
{
	return;
}

void Motor::writeENA(GpioPinValue value)
{
	return;
}

void Motor::writeENB(GpioPinValue value)
{
	return;
}