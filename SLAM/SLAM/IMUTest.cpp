#include "GpioDefs.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_BNO055.h"
#include "imumaths.h"
#include "stdio.h"
#include "stdlib.h"
#include "unisd.h"

unsigned int sleep(unsigned int seconds);

//Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup(void)
{
	  Serial.begin(9600);
	  Serial.println("Orientation Sensor Test"); Serial.println("");
	
		   //Initialize the sensor
		  if (!bno.begin())
		  {
				//There was a problem detecting the BNO055 ... check your connections
			    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
		    while (1);
		  }
		
		  sleep(1000);
	
		  bno.setExtCrystalUse(true);
	}

void loop(void)
{
	    //Get a new sensor event 
		sensors_event_t event;
		bno.getEvent(&event);

		//Display the floating point data
		printf("X: ");
		printf(event.orientation.x, 4);
		printf("\tY: ");
		printf(event.orientation.y, 4);
		printf("\tZ: ");
		printf(event.orientation.z, 4);
		printf("");
	
		  sleep(100);
	}
