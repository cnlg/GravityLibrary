/*
 Name:		Accelerometer_FXLN8361_S.h
 Created:	2017/8/24 10:20:32
 Author:	amy.liao@dfrobot.com
 Company:	DFRobot
*/

#ifndef _Accelerometer_FXLN8361_S_h
#define _Accelerometer_FXLN8361_S_h

#include "Arduino.h"

class Accelerometer_FXLN8361_S
{
public:
	Accelerometer_FXLN8361_S();
	~Accelerometer_FXLN8361_S();

public:
	float acceleration_x(int Pin_x);
	float acceleration_y(int Pin_y);
	float acceleration_z(int Pin_z);

private:

	float x;  //x axis residue voltage under 0 m/s^2
	float y; //y axis residue voltage under 0 m/s^2
	float z; //z axis residue voltage under 0 m/s^2
	float g; //the voltage under acceleration 9.8 m/s^2, by defalut g = 0.235 mv

};


#endif