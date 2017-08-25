/*
 Name:		Accelerometer_FXLN8361_S.cpp
 Created:	2017/8/24 10:20:32
 Author:	amy.liao@dfrobot.com
 Company:	DFRobot
*/

#include "Accelerometer_FXLN8361_S.h"

Accelerometer_FXLN8361_S::Accelerometer_FXLN8361_S(): x(0.774), y(0.781), z(0.923), g(0.235)
{
}

Accelerometer_FXLN8361_S::~Accelerometer_FXLN8361_S()
{
}

float Accelerometer_FXLN8361_S::acceleration_x(int Pin_x)
{
	return (analogRead(Pin_x) * 5 / 1024.0 - x) / g;
}

float Accelerometer_FXLN8361_S::acceleration_y(int Pin_y)
{
	return(analogRead(Pin_y) * 5 / 1024.0 - y) / g;
}

float Accelerometer_FXLN8361_S::acceleration_z(int Pin_z)
{
	return (analogRead(Pin_z) * 5 / 1024.0 - z) / g;
}
