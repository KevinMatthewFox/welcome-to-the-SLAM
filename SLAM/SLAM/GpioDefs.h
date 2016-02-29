#pragma once

//
// File: GpioDefs.h
// Author: Kevin Fox
// 

#define GPIO4 4 //Pin for the transmitter
#define GPIO5 5 //Receiver
#define GPIO6 6 //INFRAD SENSOR1 INPUT
#define GPIO12 12 //INFRAD SENSOR2 INPUT
#define GPIO13 13 //INFRAD SENSOR3 INPUT
#define GPIO16 16 //INA Left
#define GPIO18 18 //INB Left
#define GPIO19 19 //INA Right
#define GPIO22 22 //INB Right
#define GPIO20 20 //PWM
#define GPIO21 21 //INFRAD SENSOR1 OUTPUT
#define GPIO22 22 //INFRAD SENSOR2 OUTPUT
#define GPIO23 23 //INFRAD SENSOR3 OUTPUT
#define GPIO24 24 //ENA Left
#define GPIO25 25 //ENB Left
#define GPIO26 26 //ENA Right
#define GPIO27 27 //ENB Right

#define HIGH GpioPinValue::High //1
#define LOW GpioPinValue::Low //0
#define OUTPUT GpioPinDriveMode::Output //1
#define OUTPUTOD GpioPinDriveMode::OutputOpenDrain //4
#define OUTPUTOS GpioPinDriveMode::OutputOpenSource //6
#define OUTPUTODPU GpioPinDriveMode::OutputOpenDrainPullUp //5
#define OUTPUTOSPD GpioPinDriveMode::OutputOpenSourcePullDown //7
#define INPUT GpioPinDriveMode::Input //0
#define INPUTPU GpioPinDriveMode::InputPullUp //2
#define INPUTPD GpioPinDriveMode::InputPullDown //3