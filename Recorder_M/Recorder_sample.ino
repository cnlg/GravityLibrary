/*
 Name:		Recorder_sample.ino
 Created:	2017/8/24
 Author:	amy.liao@dfrobot.com
 Company:	DFRobot
*/

#include "Recorder_M.h"

Recorder_M recoder;

void setup()
{
    recoder.setPin(2);
}

void loop()
{
    recoder.play();
}