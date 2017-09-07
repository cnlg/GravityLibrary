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
    this->_playPin = playPin;
    digitalWrite(this->_playPin,LOW);
}

void Recorder_M::play()
{
    digitalWrite(this->_playPin,HIGH);
    delay(1000);
}
