// 
// File name: motor.h
// Author: Kevin Fox, Jiaxiang Wang
// Senior Engineering Design 498
// University of Arizona
// Team 15017
// Autonomous Mapping
//

#pragma once

void goForward(); //both motors forward

void goLeft();

void goRight();

void goIdle(); //motors off

void goRotRight(); //rotate to the right - left motor forward, right motor reverse

void goRotLeft(); //rotate to the left - left motor reverse, right motor forward

void goReverse();