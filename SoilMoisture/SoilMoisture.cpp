#include <Arduino.h>
#include "SoilMoisture.h"

SoilMoisture::SoilMoisture():_soilMoistureValue(0),_airValue(0),_waterValue(0),_intervals(0)
{

}

SoilMoisture::~SoilMoisture()
{

}

void SoilMoisture::setPin(int pin)
{
    this->_pin = pin;
}

void SoilMoisture::setAirWaterValue(int airValue,int waterValue)
{
    this->_airValue = airValue;
    this->_waterValue = waterValue;
    this->_intervals = (airValue - waterValue)/3;
}

void SoilMoisture::setup()
{
    pinMode(_pin,INPUT);
}

void SoilMoisture::update()
{
    if(millis() - this->_currentTime > 100)
    {
         _currentTime = millis();
        _soilMoistureValue = analogRead(_pin);
        if(this->_handleVeryWet && _soilMoistureValue > _waterValue && _soilMoistureValue < (_waterValue + _intervals))
        {
            this->_handleVeryWet(this->_soilMoistureValue);
        }
        if(this->_handleWet && _soilMoistureValue > (_waterValue + _intervals) && _soilMoistureValue < (_airValue - _intervals))
        {
            this->_handleWet(this->_soilMoistureValue);
        }
        if(this->_handleDry && _soilMoistureValue < _airValue && _soilMoistureValue > (_airValue - _intervals))
        {
            this->_handleDry(this->_soilMoistureValue);
        }
    }
}

int SoilMoisture::getValue()
{
    return _soilMoistureValue;
}


void SoilMoisture::setHandleVeryWet(HandleFunc handleVeryWet)
{
    this->_handleVeryWet = handleVeryWet;
}

void SoilMoisture::setHandleWet(HandleFunc handleWet)
{
   this->_handleWet = handleWet;
}

void SoilMoisture::setHandleDry(HandleFunc handleDry)
{
   this->_handleDry = handleDry;
}
