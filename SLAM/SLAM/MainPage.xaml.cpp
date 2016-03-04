//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//
// Author: ENGR 498 - Team 15017
//		Kevin Fox, Jiaxiang Wang
// Description: SLAM, baby
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "MotorController.h"
#include "GpioDefs.h"
#include "Motor.h"
#include "MotorTest.h"
#include <iostream>

using namespace SLAM;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Devices::Gpio;
using namespace Windows::Devices::Pwm;
using namespace Windows::Devices::Enumeration;

//using namespace System;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	//Declarations -- Controllers
	GpioController ^gpio = GpioController::GetDefault();
	//PwmController ^pwm = nullptr;
	//pwm->GetDefaultAsync(); 

	//Declarations -- Pins
	GpioPin ^inputTransmitter = nullptr;
	GpioPin ^outputTransmitter = nullptr;
	GpioPin ^infradSensor1 = nullptr;
	GpioPin ^infradSensor2 = nullptr;
	GpioPin ^infradSensor3 = nullptr;
	GpioPin ^output1 = nullptr;
	GpioPin ^output2 = nullptr;
	GpioPin ^output3 = nullptr;
	//PwmPin ^motor1 = nullptr;
	//PwmPin ^motor2 = nullptr;
	//motor1 = pwm->OpenPin(GPIO26);
	//motor2 = pwm->OpenPin(GPIO27);
	//motor1->SetActiveDutyCyclePercentage(90);
	//motor2->SetActiveDutyCyclePercentage(90);

	//Initialization -- Motors
	Motor *motorLeft = nullptr;
	Motor *motorRight = nullptr;
	motorLeft = new Motor(GPIO20, /*pwm, 100.0,*/ gpio, GPIO16, GPIO18, GPIO24, GPIO25);   //const int pwnPinNum, PwmController ^pwmController, double dutyCycle, GpioController ^gpio, const int inA, const int inB, const int enA, const int enB
	motorRight = new Motor(GPIO21, /*pwm, 100.0,*/ gpio, GPIO19 , GPIO22, GPIO26, GPIO27);

	//Initialization -- Motor Controller -- this needs to come after the motor initialization because we feed two motors into the controller
	MotorController *motorController = nullptr;
	motorController = new MotorController(motorLeft, motorRight); //THIS IS COPYING THE POINTERS

	//Testing the motor
	
	//Initializations -- Transmitters, Sensors
	inputTransmitter = gpio->OpenPin(GPIO4);
	//outputTransmitter = gpio->OpenPin(GPIO5);
	//infradSensor1 = gpio->OpenPin(GPIO6);
	//infradSensor2 = gpio->OpenPin(GPIO12);
	//infradSensor3 = gpio->OpenPin(GPIO13);
	//output1 = gpio->OpenPin(GPIO16);
	//output2 = gpio->OpenPin(GPIO18);
	//output3 = gpio->OpenPin(GPIO22);
	


	//Testing for gpiocontroller
	if (gpio == nullptr)
	{
		inputTransmitter = nullptr;
		outputTransmitter = nullptr;
		infradSensor1 = nullptr;
		infradSensor2 = nullptr;
		infradSensor3 = nullptr;
		output1 = nullptr;
		output2 = nullptr;
		output3 = nullptr;

		std::cout << "There is no GPIO controller on this device.";
		return;
	}
	/*
	else if (pwm == nullptr)
	{
		std::cout << "There is no PWM controller on this device";
	}
	*/
	else
	{
		//if (inputTransmitter->IsDriveModeSupported(INPUTPU))
		//{
		//	inputTransmitter->SetDriveMode(INPUTPU);
		//}
		//else
		//{
		//	inputTransmitter->SetDriveMode(INPUT);
		//}
		inputTransmitter->SetDriveMode(INPUT);
		//outputTransmitter->SetDriveMode(OUTPUT);
		//infradSensor1->SetDriveMode(INPUT);
		//infradSensor2->SetDriveMode(INPUT);
		//infradSensor3->SetDriveMode(INPUT);
		//output1->SetDriveMode(OUTPUT);
		//output2->SetDriveMode(OUTPUT);
		//output3->SetDriveMode(OUTPUT);

		motorTest(motorController, inputTransmitter);
		//TimeSpan inputDebounce;
		//inputDebounce.Duration = 50000;

		//inputTransmitter->DebounceTimeout = inputDebounce;

		
		//while (1) {
		//	
		//	//Transmitter code
		//	if (inputTransmitter->Read() == HIGH) {
		//		outputTransmitter->Write(HIGH);
		//		outputTransmitter->Write(HIGH);
		//	}
		//	else {
		//		outputTransmitter->Write(LOW);
		//		outputTransmitter->Write(LOW);
		//	}
		//		
		//	//Infrared sensor code
		//	if (infradSensor1->Read() == HIGH)
		//		output1->Write(HIGH);
		//	else
		//		output1->Write(LOW);
		//	if (infradSensor2->Read() == HIGH)
		//		output2->Write(HIGH);
		//	else
		//		output2->Write(LOW);
		//	if (infradSensor3->Read() == HIGH)
		//		output3->Write(HIGH);
		//	else
		//		output3->Write(LOW);

		//}



	}

	/*Close Pins
	~inputTransmitter;// = gpio->OpenPin(gpio4);
	~outputTransmitter;// = gpio->OpenPin(gpio5);
	~infradSensor1; //= gpio->OpenPin(gpio6);
	~infradSensor2; //= gpio->OpenPin(gpio12);
	~infradSensor3; //= gpio->OpenPin(gpio13);
	~output1; //= gpio->OpenPin(gpio16);
	~output2; //= gpio->OpenPin(gpio18);
	~output3; //= gpio->OpenPin(gpio22);
	~motor1; //= pwm->OpenPin(gpio26);
	~motor2; //= pwm->OpenPin(gpio27);
	*/

	//NEED TO DELETE DYNAMICALLY ALLOCATED OBJECTS TO AVOID MEMORY LEAK

	return;
}

/*void SLAM::MainPage::inputButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	greetingOutput->Text = "Hello, " + nameInput->Text + "!";
}*/