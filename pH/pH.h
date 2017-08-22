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

typedef void (*pFunc)(double pHValue);

class Ph
{
public:
    Ph();
    ~Ph() {};

public:
    void setPin(int pin);
    void setOffset(float offset);
    //初始化
    void setup();

    //更新传感器数据
    void update();

    //获取传感器数据
    double getValue();
    void setHandleM(pFunc handleM, double maxPhValue);
    void setHandleL(pFunc handleL, double minPhValue);

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

    pFunc _handleM = 0;
    pFunc _handleL = 0;
    double _maxPhValue;
    double _minPhValue;
    
    static const int arrayLength = 5;
    int pHArray[arrayLength];   //储存传感器返回数据的平均值 
    void handleCallback();
};

#endif
