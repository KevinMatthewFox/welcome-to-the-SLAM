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

using namespace Windows::Devices::Gpio;
using namespace Windows::Devices::Pwm;

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