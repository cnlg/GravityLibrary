/*
  DFRobotHighTemperatureSensor.cpp - DFRobotHighTemperatureSensor library
  Developed by Bernie - 2016/1/13

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

HighTemperature Sensor info found at
http://www.dfrobot.com/

Version 1.0: 13 Jan 2016 by bernie
- Updated to build against Arduino 1.0.6
- Made accessors inline in the header so they can be optimized away
*/

#include<Arduino.h>
#include "DFRobotHighTemperatureSensor.h"

DFRobotHighTemperature::DFRobotHighTemperature():_voltageRef(5.000)  //Constructor,Default reference voltage 5.000
{
    this->_handleM = 0;
    this->_handleL = 0;

}


DFRobotHighTemperature::~DFRobotHighTemperature()		//Destructor
{
	
}

void DFRobotHighTemperature::setPin(int pin)
{
    this->_pin = pin;
    pinMode(this->_pin,INPUT);
}

void DFRobotHighTemperature::setup()
{
    pinMode(this->_pin,INPUT);
}

void DFRobotHighTemperature::setVoltageRef(float voltage)
{
    this->_voltageRef = voltage;
}

int DFRobotHighTemperature::getValue()
{
    return this->_temperature;
}

void DFRobotHighTemperature::setHandleM(pFunc handleM,float maxTemperature)
{
   this->_handleM = handleM;
   this->_maxTemperature = maxTemperature; 
}

void DFRobotHighTemperature::setHandleL(pFunc handleL,float minTemperature)
{
   this->_handleL = handleL;
   this->_maxTemperature = minTemperature; 
}

void DFRobotHighTemperature::update()     //Get temperature
{
    float voltage = 0;
    float res = 0;
    int front = 0;
    int end = 399;
    int mid = 0;
    int   sensorValue = analogRead(this->_pin);
    voltage = sensorValue * _voltageRef / 1024.0;  //If your microcontroller are a 12 bit ADC, you should be change 1024 to 4096
	//If you have a DS18B20 on hand, you can make a more accurate calibration.
	//change 220.9 to 210.9 or 230.9,and you need change 2.209 to 2.109 or 2.309 at the same time to accurate calibration.
	res =  (1800 * voltage + 220.9 * 18) / (2.209 * 18 - voltage);
	//res =  (1800 * voltage + 235.9 * 18) / (2.359 * 18 - voltage);
	//searched by the halving method
    mid = (front + end) / 2;
    while (front < end && pgm_read_float(&PT100Tab[mid]) != res)  
        {
            if (pgm_read_float(&PT100Tab[mid]) < res)
                if (pgm_read_float(&PT100Tab[mid + 1]) < res)
                    front = mid + 1;
                else
                    {
                        mid = comp(res, mid);
                        return mid;
                    }
            if (pgm_read_float(&PT100Tab[mid]) > res)
                if (pgm_read_float(&PT100Tab[mid - 1]) > res)
                    end = mid - 1;
                else
                    {
                        mid = comp(res, mid - 1);
                        return mid;
                    }
            mid = front + (end - front) / 2;
        }
    this->_temperature = mid;
    handleCallback();
}
int DFRobotHighTemperature::comp(float pt, int i) //Which number is closer on the two adjacent numbers.
{
    if ((pt - pgm_read_float(&PT100Tab[i])) > (pgm_read_float(&PT100Tab[i + 1]) - pgm_read_float(&PT100Tab[i])) / 2 )
        return i + 1;
    else
        return i;
}

void DFRobotHighTemperature::handleCallback()
{
    if(this->_handleM && this->_temperature > this->_maxTemperature)
    {
        this->_handleM(this->_temperature);
    }
    if(this->_handleL && this->_temperature < this->_minTemperature)
    {
        this->_handleL(this->_temperature);
    }
}
