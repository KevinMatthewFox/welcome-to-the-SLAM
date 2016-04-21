// 
// File name: checkHealth.cpp
// Author: Kevin Fox
// Senior Engineering Design 498
// University of Arizona
// Team 15017
// Autonomous Mapping
//

#include <cstdio>
#include "rplidar.h"
#include "check_health.h"

using namespace rp::standalone::rplidar; //rplidar namespace

bool checkRPLIDARHealth(RPlidarDriver * drv)
{
    u_result     op_result;
    rplidar_response_device_health_t healthinfo;


    op_result = drv->getHealth(healthinfo);
    if (IS_OK(op_result)) // the macro IS_OK is the preperred way to judge whether the operation is succeed.
	{ 
        printf("RPLidar health status : %d\n", healthinfo.status);
        if (healthinfo.status == RPLIDAR_STATUS_ERROR) 
		{
            fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
            // enable the following code if you want rplidar to be reboot by software
            // drv->reset();
            return false;
        } 
		else 
		{
            return true;
        }

    } 
	else 
	{
        fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
        return false;
    }
}