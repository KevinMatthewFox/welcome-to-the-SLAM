#pragma once

//
// File: GpioDefs.h
// Author: Kevin Fox
// 

#define GPIO2 2//Pin for IMU SDA (I2C)
#define GPIO3 3 //Pin for IMU SCL (I2C)
#define GPIO4 4 //Pin for the transmitter
#define GPIO5 5 //Receiver
#define GPIO6 6 //INFRAD SENSOR1 INPUT
#define GPIO12 12 //INFRAD SENSOR2 INPUT
#define GPIO13 13 //INFRAD SENSOR3 INPUT
#define GPIO16 16 //INA Left
#define GPIO18 18 //INB Left
#define GPIO19 19 //INA Right PullDown; header pin 35
#define GPIO20 20 //PWM PullDown; header pin 38
#define GPIO21 21 //INFRAD SENSOR1 OUTPUT PullDown; header pin 40
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