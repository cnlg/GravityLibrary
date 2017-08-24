/*
 Name:		LEDString_M.cpp
 Created:	2017/8/24
 Author:	amy.liao@dfrobot.com
 Company:	DFRobot
*/

#include "LEDString_M.h"

LEDString_M ledString;

void setup()
{
    ledString.setPin(3);
}

void loop()
{
    ledString.Brightness(127);
    ledString.breath();
}