/*
Name:		Accelerometer_FXLN8361_S.cpp
Created:	2017/8/24 10:20:32
Author:	amy.liao@dfrobot.com
Company:	DFRobot
*/

#include "Arduino.h"
#include "Accelerometer_FXLN8361_S.h"

Accelerometer_FXLN8361_S accelerometer;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Serial.print("x= ");
	Serial.println(accelerometer.acceleration_x(0));//read from pin 0

	Serial.print("y= ");
	Serial.println(accelerometer.acceleration_y(1));	//read from pin 1

	Serial.print("z= ");
	Serial.println(accelerometer.acceleration_z(2));//read from pin 2

	delay(500);
}