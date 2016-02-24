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
	 // 
	//Definitions
	GpioPinValue high = GpioPinValue::High; //1
	GpioPinValue low = GpioPinValue::Low; //0
	GpioPinDriveMode output = GpioPinDriveMode::Output; //1
	//GpioPinDriveMode outputOD = GpioPinDriveMode::OutputOpenDrain; //4
	//GpioPinDriveMode outputOS = GpioPinDriveMode::OutputOpenSource; //6
	//GpioPinDriveMode outputODPU = GpioPinDriveMode::OutputOpenDrainPullUp; //5
	//GpioPinDriveMode outputOSPD = GpioPinDriveMode::OutputOpenSourcePullDown; //7
	GpioPinDriveMode input = GpioPinDriveMode::Input; //0
	//GpioPinDriveMode inputPU = GpioPinDriveMode::InputPullUp; //2
	//GpioPinDriveMode inputPD = GpioPinDriveMode::InputPullDown; //3
	//GpioPinValue Read();



	//GPIO pins - uncomment the ones needed
	const int gpio4 = 4; //Pin for the transmitter
	const int gpio5 = 5; //Receiver
	const int gpio6 = 6; //Infrad sensor1 input
	const int gpio12 = 12; //Infrad sensor2 input
	const int gpio13 = 13; //Infrad sensor3 input
	const int gpio16 = 16; //Infrad sensor1 output
	const int gpio18 = 18; //Infrad sensor2 output
	const int gpio22 = 22; //Infrad sensor3 output
	//const int gpio19 = 19; //PullDown; header pin 35
	//const int gpio20 = 20; //PullDown; header pin 38
	//const int gpio21 = 21; //PullDown; header pin 40
	//const int gpio22 = 22; //PullDown; header pin 15
	//const int gpio23 = 23; //PullDown; header pin 16
	//const int gpio24 = 24; //PullDown; header pin 18
	//const int gpio25 = 25; //PullDown; header pin 22
	const int gpio26 = 26; //PullDown; header pin 37
	const int gpio27 = 27; //PullDown; header pin 13

	//Declarations
	GpioController ^gpio = GpioController::GetDefault();
	PwmController ^pwm;

	GpioPin ^inputTransmitter = nullptr;
	GpioPin ^outputTransmitter = nullptr;
	GpioPin ^infradSensor1 = nullptr;
	GpioPin ^infradSensor2 = nullptr;
	GpioPin ^infradSensor3 = nullptr;
	GpioPin ^output1 = nullptr;
	GpioPin ^output2 = nullptr;
	GpioPin ^output3 = nullptr;
	PwmPin ^motor1 = nullptr;
	PwmPin ^motor2 = nullptr;
	
	motor1 = pwm->OpenPin(gpio26);
	motor2 = pwm->OpenPin(gpio27);
	motor1->SetActiveDutyCyclePercentage(90);
	motor2->SetActiveDutyCyclePercentage(90);
	


	inputTransmitter = gpio->OpenPin(gpio4);
	outputTransmitter = gpio->OpenPin(gpio5);
	infradSensor1 = gpio->OpenPin(gpio6);
	infradSensor2 = gpio->OpenPin(gpio12);
	infradSensor3 = gpio->OpenPin(gpio13);
	output1 = gpio->OpenPin(gpio16);
	output2 = gpio->OpenPin(gpio18);
	output3 = gpio->OpenPin(gpio22);
	






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
	else
	{
		inputTransmitter->SetDriveMode(input);
		outputTransmitter->SetDriveMode(output);
		infradSensor1->SetDriveMode(input);

		Motor *motorController;
		motorController->goIdle(motor1, motor2);

		infradSensor2->SetDriveMode(input);
		infradSensor3->SetDriveMode(input);
		output1->SetDriveMode(output);
		output2->SetDriveMode(output);
		output3->SetDriveMode(output);




		while (1) {
			
			if (inputTransmitter->Read() == high) {
				outputTransmitter->Write(high);
				outputTransmitter->Write(high);
			}
			else {
				outputTransmitter->Write(low);
				outputTransmitter->Write(low);
			}
				

			if (infradSensor1->Read() == high)
				output1->Write(high);
			else
				output1->Write(low);
			if (infradSensor2->Read() == high)
				output2->Write(high);
			else
				output2->Write(low);
			if (infradSensor3->Read() == high)
				output3->Write(high);
			else
				output3->Write(low);



		}



	}

	//testPin = gpio->OpenPin(gpio4); //power-on the pin
	//testPin->Write(high);
	//testPin->SetDriveMode(output);

	return;
}

/*void SLAM::MainPage::inputButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	greetingOutput->Text = "Hello, " + nameInput->Text + "!";
}*/
