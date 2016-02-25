#pragma once

//
// File: GpioDefs.h
// Author: Kevin Fox
// 

#define GPIO4 4 //Pin for the transmitter
#define GPIO5 5 //Receiver
#define GPIO6 6 //Infrad sensor1 input
#define GPIO12 12 //INFRAD SENSOR2 INPUT
#define GPIO13 13 //INFRAD SENSOR3 INPUT
#define GPIO16 16 //INFRAD SENSOR1 OUTPUT
#define GPIO18 18 //INFRAD SENSOR2 OUTPUT
#define GPIO22 22 //INFRAD SENSOR3 OUTPUT
#define GPIO19 19 //PULLDOWN; HEADER PIN 35
#define GPIO20 20 //PULLDOWN; HEADER PIN 38
#define GPIO21 21 //PULLDOWN; HEADER PIN 40
#define GPIO22 22 //PULLDOWN; HEADER PIN 15
#define GPIO23 23 //PULLDOWN; HEADER PIN 16
#define GPIO24 24 //PULLDOWN; HEADER PIN 18
#define GPIO25 25 //PULLDOWN; HEADER PIN 22
#define GPIO26 26 //PULLDOWN; HEADER PIN 37
#define GPIO27 27 //PullDown; header pin 13

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