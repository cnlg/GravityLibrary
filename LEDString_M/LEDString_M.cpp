/*
 Name:		LEDString_M.cpp
 Created:	2017/8/24
 Author:	amy.liao@dfrobot.com
 Company:	DFRobot
*/

#include "LEDString_M.h"

LEDString_M::LEDString_M():_bright(255)
{
}

LEDString_M::~LEDString_M()
{
}

void LEDString_M::setPin(uint8_t LightPin)
{
    _LightPin = LightPin;
    pinMode(_LightPin, OUTPUT);
}

void LEDString_M::Brightness(uint8_t bright)
{
    _bright = bright;
    analogWrite(_LightPin, _bright);
}

void LEDString_M::breath(int speed = 10)
{
    uint8_t t;
    _speed = speed;
    for(t = 5; t < _bright; t++ )
    { 
     analogWrite(_LightPin, t);   
     delay(_speed);
    }      
    for(t = _bright; t > 5; t--) 
    {
       analogWrite(_LightPin, t); 
       delay(_speed); 
    }          
}