/*
 Name:		Recorder_M.h
 Created:	2017/8/24
 Author:	amy.liao@dfrobot.com
 Company:	DFRobot
*/

#ifndef _RECORDER_M_
#define _RECORDER_M_

#include "Arduino.h"

class Recorder_M
{
    public:
    Recorder_M();
    ~Recorder_M();

    public:
    void setPin();
    void play();

    private:
    uint8_t _playPin;

}

#endif
