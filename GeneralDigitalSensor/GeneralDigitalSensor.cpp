#include <Arduino.h>
#include "GeneralDigitalSensor.h"

GeneralDigitalSensor::GeneralDigitalSensor():_interval(0),_handleM(0),_handleL(0)
{
}

GeneralDigitalSensor::~GeneralDigitalSensor()
{
}

void GeneralDigitalSensor::setPin(uint8_t pin, uint8_t mode)
{
    this->_pin = pin;
    pinMode(pin,mode);
}

int GeneralDigitalSensor::getValue()
{
    return this->_value; 
}

void GeneralDigitalSensor::setValue(uint8_t value)
{
    digitalWrite(this->_pin,value);
}

void GeneralDigitalSensor::setHandleM(pFunc handleM,int maxValue)
{
    this->_handleM = handleM;
    this->_maxValue = maxValue;
}

void GeneralDigitalSensor::setHandleL(pFunc handleL,int minValue)
{
    this->_handleL = handleL;
    this->_minValue = minValue;
}

void GeneralDigitalSensor::setInterval(unsigned long interval)
{
    this->_interval = interval;
}

void GeneralDigitalSensor::update()
{
    static unsigned long previous = millis();
    if(this->_interval == 0)
    {
        this->_value = digitalRead(this->_pin);
    }
    else if(millis() - previous >= this->_interval) 
    {
        previous = millis();
        this->_value = digitalRead(this->_pin);
    }
    handleCallback();
}

void GeneralDigitalSensor::handleCallback()
{
    if(this->_handleM && this->_value >= this->_maxValue)
    {
        this->_handleM(this->_value);
    }
    if(this->_handleL && this->_value <= this->_minValue)
    {
        this->handleL(this->_value);
    }
}
