/*********************************************************************
* Ph.cpp
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Monitoring water quality parameters ph
*
* Product Links：http://www.dfrobot.com.cn/goods-812.html
*
* Sensor driver pin：A2 (_pin(A2))
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-07
**********************************************************************/

#include "pH.h"

Ph::Ph():_pin(A2), _sum(0),_offset(0.0f), 
_interval(30),_pHValue(0),_voltage(0)
{
}

//********************************************************************************************
// 函数名称: setup()
// 函数说明：初始化ph传感器
//********************************************************************************************

void Ph::setPin(int pin)
{
	this->_pin = pin;
	pinMode(this->_pin, INPUT);
}

void Ph::setOffset(float offset)
{
    this->_offset = offset;
}


void Ph::setInterval(unsigned long interval)
{
	this->_interval = interval;
}
//********************************************************************************************
// 函数名称: update()
// 函数说明：更新传感器数值
//********************************************************************************************
void Ph::update()
{
	static unsigned long previousTime = millis();
	static int pHArrayIndex = 0;
	if (millis() - previousTime >= this->_interval)
	{
		previousTime = millis();
		pHArray[pHArrayIndex++] = analogRead(this->_pin);

		if (pHArrayIndex == arrayLength)  // 5*30 = 150ms计算一次
		{
			pHArrayIndex = 0;
			for (int i = 0; i < arrayLength; i++)
				this->_sum += pHArray[i];
			this->_averageVoltage = this->_sum / arrayLength;
			this->_sum = 0;
			this->_voltage = this->_averageVoltage*5.0 / 1024.0;
			this->_pHValue = 3.5*this->_voltage + this->_offset;
		}			
	}
}


//********************************************************************************************
// 函数名称: getValue()
// 函数说明：获取传感器数据***********************************************
double Ph::getValue()
{
    return this->_pHValue;
}



