// 
// File name: main.cpp
// Author: Kevin Fox
// Senior Engineering Design 498
// University of Arizona
// Team 15017
// Autonomous Mapping
//

#include <cstdio>
#include <cstdlib>
#include <wiringPi.h>
#include <softPwm.h>
#include "rplidar.h"
#include "motor.h"

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

using namespace rp::standalone::rplidar; //rplidar namespace

int main (int argc, char* argv[])
{
	////**** MOTOR INITIALIZATION ****////
	wiringPiSetup();
	pinMode(0, INPUT); // Header Pin 11
	pinMode(7, OUTPUT); // Header Pin 7
	pinMode(5, OUTPUT); // Header Pin 18
	pinMode(6, OUTPUT); // Header Pin 22
	pinMode(27, OUTPUT); // Header Pin 36
	pinMode(1, OUTPUT); // Header Pin 12
	pinMode(25, OUTPUT); // Header Pin 37
	pinMode(2, OUTPUT); // Header Pin 13
	pinMode(24, OUTPUT); // Header Pin 35
	pinMode(3, OUTPUT); // Header Pin 15

	softPwmCreate(28, 0, 100); // Creating pwm pins - header pin 38
	softPwmCreate(29, 0, 100); // Header Pin 40
	////**** END MOTOR INITIALIZATION ****////
	
	////**** RPLIDAR INITIALIZATION ****////
	const char	*opt_com_path = NULL;
	_u32		opt_com_baudrate = 115200;
	u_result	op_result;
	
	// read serial port from the command line...
    if (argc > 1) 
	{
		opt_com_path = argv[1]; // or set to a fixed value: e.g. "com3" 
	}
	else
	{
	}
	
	// read baud rate from the command line if specified...
    if (argc > 2) 
	{
		opt_com_baudrate = strtoul(argv[2], NULL, 10);
	}
	else
	{
	}
	
	if (!opt_com_path) 
	{
		#ifdef _WIN32
			// use default com port
			opt_com_path = "\\\\.\\com3";
		#else
			opt_com_path = "/dev/ttyUSB0";
		#endif
    }
	else
	{
	}
	
	// create the driver instance
    RPlidarDriver *drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);
	
	if (!drv) 
	{
        fprintf(stderr, "insufficent memory, exit\n");
        exit(-2);
    }
	else
	{
	}
	
	// make connection...
    if (IS_FAIL(drv->connect(opt_com_path, opt_com_baudrate))) 
	{
        fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
            , opt_com_path);
        goto on_finished;
    }
	else
	{
	}
	
	// check health...
    if (!checkRPLIDARHealth(drv)) 
	{
        goto on_finished;
    }
	////**** END RPLIDAR INITIALIZATION ****////
	
	////**** BEGIN RPLIDAR SCAN ****////
	drv->startScan();

    // This is fetching the result and printing it out - will edit when finalized with other systems
    while (1) 
	{
        rplidar_response_measurement_node_t nodes[360*2];
        size_t   count = _countof(nodes);

        op_result = drv->grabScanData(nodes, count);

        if (IS_OK(op_result)) {
            drv->ascendScanData(nodes, count);
            for (int pos = 0; pos < (int)count ; ++pos) {
                printf("%s theta: %03.2f Dist: %08.2f Q: %d \n", 
                    (nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ?"S ":"  ", 
                    (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f,
                    nodes[pos].distance_q2/4.0f,
                    nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
            }
        }

    }
	
	on_finished:
		RPlidarDriver::DisposeDriver(drv);
		return 0;
	////**** END RPLIDAR SCAN ****////
}

//Ryan's code from newmotor.c
/*
	while (1) {
		if (digitalRead(0) == HIGH)
		{
			softPwmWrite(28,100);
			softPwmWrite(29,30);
			digitalWrite(7, HIGH);
			goForward();
		}
		else {
			
			softPwmWrite(28,0);
			softPwmWrite(29,0);
			digitalWrite(7, LOW);
		}
	}
*/