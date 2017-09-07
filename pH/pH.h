/*********************************************************************
* Ph.h
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
* Sensor driver pin：A2 
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-07
**********************************************************************/
#ifndef _PH_H_
#define _PH_H_

#include <Arduino.h>

class Ph
{
public:
    Ph();
    ~Ph() {};

public:
    void setPin(int pin);
    void setOffset(float offset);
    //设置刷新时间，默认时间30ms
    void setInterval(unsigned long interval);

    //更新传感器数据
    void update();

    //获取传感器数据
    double getValue();

private:
    //ph传感器引脚
    int    _pin;          
    //抽取样本间隔
    double _sum;
    float  _offset;
    int    _interval;   
	double _pHValue;
    double _voltage;
    double _averageVoltage;

    static const int arrayLength = 5;
    int pHArray[arrayLength];   //储存传感器返回数据的平均值 
};

#endif

   
