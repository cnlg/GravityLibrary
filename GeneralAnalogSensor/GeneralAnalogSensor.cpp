#include <Arduino.h>
#include "GeneralAnalogSensor.h"

GeneralAnalogSensor::GeneralAnalogSensor():_interval(0),_handleM(0),_handleL(0)
{
}

GeneralAnalogSensor::~GeneralAnalogSensor()
{
}

void GeneralAnalogSensor::setPin(uint8_t pin, uint8_t mode)
{
    this->_pin = pin;
    pinMode(pin,mode);
}

int GeneralAnalogSensor::getValue()
{
    return this->_value; 
}

void GeneralAnalogSensor::setValue(int value)
{
    analogWrite(this->_pin,value);
}

void GeneralAnalogSensor::setInterval(unsigned long interval)
{
    this->_interval = interval;
}

void GeneralAnalogSensor::setHandleL(pFunc handleL,int minvalue)
{
    this->_handleL = handleL;
    this->_minValue = minvalue;
}

void GeneralAnalogSensor::setHandleM(pFunc handleM,int maxvalue)
{
    this->_handleM = handleM;
    this->_maxValue = maxvalue;
}

void GeneralAnalogSensor::update()
{
    static unsigned long previous = millis();
    if(this->_interval == 0)
    {
        this->_value = analogRead(this->_pin); 
    }
    else if(millis() - previous >= this->_interval)
    {
        previous = millis();
        this->_value = analogRead(this->_pin); 
    }
    handleCallback();
}

void GeneralAnalogSensor::handleCallback()
{
    if(this->_handleM && this->_value >= this->_maxValue)
    {
        this->_handleM(this->_value);
    }
    if(this->_handleL && this->_value <= this->_minValue)
    {
        this->_handleL(this->_value);
    }
}

