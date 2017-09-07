/*
 Name:		LEDString_M.h
 Created:	2017/8/24
 Author:	amy.liao@dfrobot.com
 Company:	DFRobot
*/

#ifndef _LEDString_M_h
#define _LEDString_M_h

#include "Arduino.h"

class LEDString_M
{
    public:
    LEDString_M();
    ~LEDString_M();

    public:
    void setPin(uint8_t LightPin);
    void Brightness(uint8_t bright);
    void breath(int speed = 10);
    void breath();

    private:
    uint8_t _LightPin;//Pin number of light string
    uint8_t _bright;//0-255, larger the number, brighter the light 
    int _speed;//miliseconds needs per step during brightness change

}

#endif
