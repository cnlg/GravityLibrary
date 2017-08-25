#include <Arduino.h>
#include "GeneralAnalogSensor.h"

GeneralAnalogSensor::GeneralAnalogSensor():_lastTime(0)
{
    this->_handleM = 0;
    this->_handleL = 0;

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
    return analogRead(this->_pin);
}

void GeneralAnalogSensor::setValue(int value)
{
    analogWrite(this->_pin,value);
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

void GeneralAnalogSensor::update(unsigned long interval = 0)
{
    if(interval == 0)
    {
        this->_value = getValue();
    }
    else
    {
        if(millis() - this->_lastTime > interval)
        {
            this->_lastTime = millis();
            this->_value = getValue();
        }
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


