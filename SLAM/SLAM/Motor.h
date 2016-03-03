#pragma once

//
// File: Motor.h
// Author: Kevin Fox
// Header file for MotorC class
//

/* Ryan's code
class Motor
{

GpioController ^gpio = GpioController::GetDefault();
GpioPinValue high = GpioPinValue::High; //1
GpioPinValue low = GpioPinValue::Low; //0
GpioPinDriveMode input = GpioPinDriveMode::Input; //0
GpioPinDriveMode output = GpioPinDriveMode::Output; //1
PwmController ^pwm;

void goForward(int speedLeft, int speedRight);
void goLeft(int speedLeft, int speedRight);
void goRight(int speedLeft, int speedRight);
void goIdle();

GpioPin ^INA = nullptr;
GpioPin ^INB = nullptr;
GpioPin ^ENA = nullptr;
GpioPin ^ENB = nullptr;

PwmPin ^motorLeft = nullptr;
PwmPin ^motorRight = nullptr;

};
*/

//USE CONSTRUCTOR

using namespace Windows::Devices::Gpio;
using namespace Windows::Devices::Pwm;

class Motor
{
	public:
		Motor(const int pwnPinNum, /*PwmController ^pwmController, double dutyCycle,*/ GpioController ^gpio, const int inAPin, const int inBPin, const int enAPin, const int enBPin);
		//Motor(GpioPin ^firstPWMPin, /*PwmController ^pwmController, double dutyCycle,*/ GpioController ^gpio, const int inAPin, const int inBPin, const int enAPin, const int enBPin);
		//Motor(); //default constructor
		/*void setDutyCycle(double dutyCycle);
		double getDutyCycle();*/
		//void setPWMPin(const int inPwm, PwmController ^pwmController);
		//void setINAPin(const int inINA, GpioController ^gpio);
		//void setINBPin(const int inINB, GpioController ^gpio);
		//void setENAPin(const int inENA, GpioController ^gpio);
		//void setENBPin(const int inENB, GpioController ^gpio);
		void writeINA(GpioPinValue value);
		void writeINB(GpioPinValue value);
		void writeENA(GpioPinValue value);
		void writeENB(GpioPinValue value);
		~Motor();

	private:
		//double currDutyCycle;
		GpioPin ^pwm;
		GpioPin ^inA;
		GpioPin ^inB;
		GpioPin ^enA;
		GpioPin ^enB;

};