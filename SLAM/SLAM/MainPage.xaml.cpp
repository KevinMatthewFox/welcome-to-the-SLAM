//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
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

	//Declarations
	auto gpio = GpioController::GetDefault();
	GpioPin ^testPin;
	const int gpio4 = 4;
	GpioPinValue high = GpioPinValue::High;
	GpioPinDriveMode output = GpioPinDriveMode::Output;
	int x = 1;

	//Testing for gpiocontroller
	if (gpio == nullptr)
	{
		testPin = nullptr;
		std::cout << "There is no GPIO controller on this device.";
		return;
	}
	else
	{
		
		testPin = gpio->OpenPin(gpio4);
		testPin->Write(high);
		testPin->SetDriveMode(output);
	}

	return;
}

/*void SLAM::MainPage::inputButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	greetingOutput->Text = "Hello, " + nameInput->Text + "!";
}*/
