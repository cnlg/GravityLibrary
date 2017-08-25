/*
 Name:		Recorder_M.cpp
 Created:	2017/8/24
 Author:	amy.liao@dfrobot.com
 Company:	DFRobot
*/

#include "Recorder_M.h"

Recorder_M::Recorder_M()
{
}

Recorder_M::~Recorder_M()
{
}

void Recorder_M::setPin(uint8_t playPin)
{
    _playPin = playPin;
    digitalWrite(_playPin,LOW);
}

void Recorder_M::play()
{
    digitalWrite(_playPin,HIGH);
    delay(1000);
}