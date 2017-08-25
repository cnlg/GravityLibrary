#include <Arduino.h>
#include "GeneralDigitalSensor.h"

GeneralDigitalSensor::GeneralDigitalSensor()
{
    this->_handleM = 0;
    this->_handleL = 0;

}

GeneralDigitalSensor::~GeneralDigitalSensor()
{

}

void GeneralDigitalSensor::setPin(uint8_t pin, uint8_t mode)
{
    this->_pin = pin;
    pinMode(pin,mode);
}

uint8_t GeneralDigitalSensor::getValue()
{
    return digitalRead(this->_pin);
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

void GeneralDigitalSensor::update(unsigned long interval = 0)
{
    if(interval == 0)
        this->_value = getValue();
    else
    {
        if(millis() - this->_lastTime >= interval)
        {
            this->_lastTime = millis();
            this->_value = getValue();
        }
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
