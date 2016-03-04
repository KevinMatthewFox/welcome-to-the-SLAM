//
// File: MotorTest.h
// Author: Kevin Fox
//

#pragma once

#include "MotorController.h"

using namespace Windows::Devices::Gpio;

void motorTest(MotorController *motorController, GpioPin ^inputTransmitter);