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
using namespace Windows::Devices::Enumeration;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	//Definitions
	GpioPinValue high = GpioPinValue::High;
	GpioPinValue low = GpioPinValue::Low;
	GpioPinDriveMode output = GpioPinDriveMode::Output;
	GpioPinDriveMode input = GpioPinDriveMode::Input;

	//GPIO pins - uncomment the ones needed
	//const int gpio4 = 4; //PullUp; header pin 7
	//const int gpio5 = 5; //PullUp; header pin 29
	//const int gpio6 = 6; //PullUp; header pin 31
	//const int gpio12 = 12; //PullDown; header pin 32
	//const int gpio13 = 13; //PullDown; header pin 33
	//const int gpio16 = 16; //PullDown; header pin 36
	//const int gpio17 = 17; //PullDown; header pin 11
	//const int gpio18 = 18; //PullDown; header pin 12
	//const int gpio19 = 19; //PullDown; header pin 35
	//const int gpio20 = 20; //PullDown; header pin 38
	//const int gpio21 = 21; //PullDown; header pin 40
	//const int gpio22 = 22; //PullDown; header pin 15
	//const int gpio23 = 23; //PullDown; header pin 16
	//const int gpio24 = 24; //PullDown; header pin 18
	//const int gpio25 = 25; //PullDown; header pin 22
	//const int gpio26 = 26; //PullDown; header pin 37
	//const int gpio27 = 27; //PullDown; header pin 13

	//Declarations
	GpioController ^gpio = GpioController::GetDefault();
	GpioPin ^testPin = nullptr;

	//Testing for gpiocontroller
	if (gpio == nullptr)
	{
		testPin = nullptr;
		std::cout << "There is no GPIO controller on this device.";
		return;
	}
	else
	{
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
