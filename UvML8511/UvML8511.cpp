#include <Arduino.h>
#include "UvML8511.h"

UvML8511::UvML8511()
{
}

UvML8511::~UvML8511()
{
}

void UvML8511::setup()
{
    pinMode(this->_pin,INPUT);
}

void UvML8511::setPin(int pin)
{
    this->_pin = pin;
}

void UvML8511::update()
{
    int uvLevel = averageAnalogRead();

    this->_voltage = 5.0 * uvLevel/1024;
    this->_uvIntensity = mapFloat(this->_voltage, 0.99, 2.9, 0.0, 15.0);

    if(this->_handleM && this->_uvIntensity > this->_maxUvValue)
    {
        this->_handleM(this->_uvIntensity);
    }
    if(this->_handleL && this->_uvIntensity < this->_minUvValue) 
    {
        this->_handleL(this->_uvIntensity);
    }
}

int UvML8511::averageAnalogRead() 
{
    int numberOfReadings = 8;
    int runningValue = 0; 

    for(int x = 0 ; x < numberOfReadings ; x++)
    {
        runningValue += analogRead(this->_pin);
    }
    runningValue /= numberOfReadings;

    return runningValue;
}

float UvML8511::mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float UvML8511::getUvValue()
{
    return this->_uvIntensity;
}

float UvML8511::getVoltageValue()
{
    return this->_voltage;
}

void UvML8511::setHandleM(pFunc handleM,float maxUvValue)
{
    this->_handleM = handleM;
    this->_maxUvValue = maxUvValue;
}

void UvML8511::setHandleL(pFunc handleL,float minUvValue)
{
    this->_handleL = handleL;
    this->_minUvValue = minUvValue;
}
