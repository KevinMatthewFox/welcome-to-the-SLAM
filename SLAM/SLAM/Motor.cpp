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

Motor::Motor(const int pwnPinNum, double dutyCycle, const int inA, const int inB, const int enA, const int enB)
{

}

Motor::Motor() //default constructor
{

}