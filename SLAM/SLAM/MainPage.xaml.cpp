//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//
// Author: ENGR 498 - Team 15017
//		Kevin Fox
// Description: SLAM, baby
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "MotorController.h"
#include "GpioDefs.h"
#include "Motor.h"
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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	//Declarations -- Controllers
	GpioController ^gpio = GpioController::GetDefault();
	PwmController ^pwm;

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

	//Initialization -- Motor Controller
	MotorController *motorController = nullptr;
	motorController = new MotorController();

	//Initialization -- Motors
	Motor *motorLeft = nullptr;
	Motor *motorRight = nullptr;
	motorLeft = new Motor(20, pwm, 100.0, gpio, 16, 18, 24, 25);   //const int pwnPinNum, PwmController ^pwmController, double dutyCycle, GpioController ^gpio, const int inA, const int inB, const int enA, const int enB
	motorRight = new Motor(20, pwm, 100.0, gpio, 19 ,22, 26, 27);

	motorController->goForward(motorLeft, motorRight);
	
	//Initializations -- Transmitters, Sensors
	inputTransmitter = gpio->OpenPin(GPIO4);
	outputTransmitter = gpio->OpenPin(GPIO5);
	infradSensor1 = gpio->OpenPin(GPIO6);
	infradSensor2 = gpio->OpenPin(GPIO12);
	infradSensor3 = gpio->OpenPin(GPIO13);
	output1 = gpio->OpenPin(GPIO16);
	output2 = gpio->OpenPin(GPIO18);
	output3 = gpio->OpenPin(GPIO22);
	


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
		inputTransmitter->SetDriveMode(INPUT);
		outputTransmitter->SetDriveMode(OUTPUT);
		infradSensor1->SetDriveMode(INPUT);
		infradSensor2->SetDriveMode(INPUT);
		infradSensor3->SetDriveMode(INPUT);
		output1->SetDriveMode(OUTPUT);
		output2->SetDriveMode(OUTPUT);
		output3->SetDriveMode(OUTPUT);


		while (1) {
			
			//Transmitter code
			if (inputTransmitter->Read() == HIGH) {
				outputTransmitter->Write(HIGH);
				outputTransmitter->Write(HIGH);
			}
			else {
				outputTransmitter->Write(LOW);
				outputTransmitter->Write(LOW);
			}
				
			//Infrared sensor code
			if (infradSensor1->Read() == HIGH)
				output1->Write(HIGH);
			else
				output1->Write(LOW);
			if (infradSensor2->Read() == HIGH)
				output2->Write(HIGH);
			else
				output2->Write(LOW);
			if (infradSensor3->Read() == HIGH)
				output3->Write(HIGH);
			else
				output3->Write(LOW);

		}



	}

	//testPin = gpio->OpenPin(gpio4); //power-on the pin
	//testPin->Write(high);
	//testPin->SetDriveMode(output);

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


//Definitions
//GpioPinValue high = GpioPinValue::High; //1
//GpioPinValue low = GpioPinValue::Low; //0
//GpioPinDriveMode output = GpioPinDriveMode::Output; //1
//GpioPinDriveMode outputOD = GpioPinDriveMode::OutputOpenDrain; //4
//GpioPinDriveMode outputOS = GpioPinDriveMode::OutputOpenSource; //6
//GpioPinDriveMode outputODPU = GpioPinDriveMode::OutputOpenDrainPullUp; //5
//GpioPinDriveMode outputOSPD = GpioPinDriveMode::OutputOpenSourcePullDown; //7
//GpioPinDriveMode input = GpioPinDriveMode::Input; //0
//GpioPinDriveMode inputPU = GpioPinDriveMode::InputPullUp; //2
//GpioPinDriveMode inputPD = GpioPinDriveMode::InputPullDown; //3
//GpioPinValue Read();



//GPIO pins - uncomment the ones needed
//const int gpio4 = 4; //Pin for the transmitter
//const int gpio5 = 5; //Receiver
//const int gpio6 = 6; //Infrad sensor1 input
//const int gpio12 = 12; //Infrad sensor2 input
//const int gpio13 = 13; //Infrad sensor3 input
//const int gpio16 = 16; //Infrad sensor1 output
//const int gpio18 = 18; //Infrad sensor2 output
//const int gpio22 = 22; //Infrad sensor3 output
//const int gpio19 = 19; //PullDown; header pin 35
//const int gpio20 = 20; //PullDown; header pin 38
//const int gpio21 = 21; //PullDown; header pin 40
//const int gpio22 = 22; //PullDown; header pin 15
//const int gpio23 = 23; //PullDown; header pin 16
//const int gpio24 = 24; //PullDown; header pin 18
//const int gpio25 = 25; //PullDown; header pin 22
//const int gpio26 = 26; //PullDown; header pin 37
//const int gpio27 = 27; //PullDown; header pin 13