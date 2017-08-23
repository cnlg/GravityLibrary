/*
  DFRobotHCHOSensor.cpp - DFRobotHCHOSensor library
  Developed by Jason - 2016/12/15

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

Gravity: HCHO Sensor info found at
http://www.dfrobot.com/

Version 1.0: 15 Dec 2016 by Jason<jason.ling@dfrobot.com@dfrobot.com>
- Updated to build against Arduino 1.0.6
- Made accessors inline in the header so they can be optimized away
*/

#include "DFRobotHCHOSensor.h"

DFRobotHCHOSensor::DFRobotHCHOSensor(HardwareSerial& hardwareSerial)	//read the uart signal by hardware uart,such as D0
{
    this->_Serial = &hardwareSerial;
    this->_useUart = true;
    this->_useGeneralPin = false;
    this->_handleM = 0;
    this->_handleL = 0;
}

DFRobotHCHOSensor::DFRobotHCHOSensor(SoftwareSerial& softwareSerial)	//read the uart signal by software uart,such as D10
{
    this->_Serial = &softwareSerial;
    this->_useUart = true;
    this->_useGeneralPin = false;
    this->_handleM = 0;
    this->_handleL = 0;
}
DFRobotHCHOSensor:: DFRobotHCHOSensor(int pin,float ref)//read the analog signal by analog input pin ,such as A2; ref:voltage on AREF pin
{
    this->_useUart = false;
    this->_useGeneralPin = true;
    this->_pin = pin;
    this->_ref = ref;											//for arduino uno ,the ref should be 5.0V(Typical)
    this->_handleM = 0;
    this->_handleL = 0;
}

void DFRobotHCHOSensor::setup()
{
    if(this->_useGeneralPin)
        pinMode(this->_pin,INPUT);
}
byte DFRobotHCHOSensor::checkSum(byte array[],byte length)	
{
    byte sum = 0;
    for(int i = 1; i < length-1; i ++)
    {
		sum += array[i];
    }
    sum = (~sum) + 1;
    return sum;
}

bool DFRobotHCHOSensor::available()		//new data was recevied
{
    while(this->_Serial->available()>0)
    {
		for(byte index = 0; index < maxLength-1; index++)
		{
			receivedCommandStack[index] = receivedCommandStack[index+1];
		}
		receivedCommandStack[maxLength-1] = this->_Serial->read();

		byte sumNum = checkSum(receivedCommandStack,maxLength);
		if( (receivedCommandStack[0] == 0xFF) && (receivedCommandStack[1] == 0x17) && (receivedCommandStack[2] == 0x04) && (receivedCommandStack[maxLength-1] == sumNum) )	//head bit and sum are all right
		{
			return 1; //new data received
		}else{
			return 0; //data loss or error
		}  
    }
    return 0;
}

void DFRobotHCHOSensor::update()
{
    if(this->_useUart && available())
    {
        uartReadPPM();
    }
    if(this->_useGeneralPin)
    {
        dacReadPPM();
    }
    if(this->_handleM && this->_ppm > this->_maxPPM)
    {
        this->_handleM(this->_ppm);
    }
    if(this->_handleL && this->_ppm < this->_minPPM)
    {
        this->_handleL(this->_ppm);
    }
}

float DFRobotHCHOSensor::getPPM()
{
    return this->_ppm;
}

void DFRobotHCHOSensor::uartReadPPM()
{
    float ppb = (unsigned int)receivedCommandStack[4]<<8 | receivedCommandStack[5];		// bit 4: ppm high 8-bit; bit 5: ppm low 8-bit
    this->_ppm = ppb / 1000.0;	//1ppb = 1000ppm
}
 
void DFRobotHCHOSensor::setHandleM(pFunc handleM,float maxPPM)
{
    this->_handleM = handleM;
    this->_maxPPM = maxPPM;
}

void DFRobotHCHOSensor::setHandleL(pFunc handleL,float minPPM)
{
    this->_handleL = handleL;
    this->_minPPM = minPPM;
}

void DFRobotHCHOSensor::dacReadPPM()
{
   float analogVoltage = analogRead(this->_pin) / 1024.0 * this->_ref;
   this->_ppm = 3.125 * analogVoltage - 1.25;	//linear relationship(0.4V for 0 ppm and 2V for 5ppm)
   if(this->_ppm<0)
	   this->_ppm = 0;
   else if(this->_ppm>5)
	   this->_ppm = 5;
}
