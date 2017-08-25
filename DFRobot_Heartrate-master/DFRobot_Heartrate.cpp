#include "DFRobot_Heartrate.h"

#define debug_ 1

uint16_t value[SAMPLE_NUMBER]={0}; ///< Initialize sampling point value


DFRobot_Heartrate::DFRobot_Heartrate(char mode):_mode(mode),_valueCount(255)
{

}


void DFRobot_Heartrate::setPin(int pin)
{
    _pin = pin;
}

/*!
* @brief Get a Sample values
*
* @brief  Get a Sample values
*
* @return uint16_t
*/ 
uint16_t DFRobot_Heartrate::getValue() 
{
	_valueCount++;
    if(_valueCount >= SAMPLE_NUMBER){
        _valueCount = 0;
    }    
	value[_valueCount] = analogRead(_pin);  
    return(value[_valueCount]);

}

/*!
* @brief Get a sample
*
* @brief  Get the current location
*
* @return uint8_t
*/ 
uint8_t DFRobot_Heartrate::getCnt(void) 
{
    return(_valueCount);
}

/*!
* @brief Points to a valid node of the wave rise
*
* @brief  When the sampling point value increased 4 times in a row, considered to be a heartbeat
*
* @return char
*/ 

char DFRobot_Heartrate::maxNumber(uint8_t count)
{
	uint16_t temp1,temp2;
	for(int i=0;i<4;i++){
		if(count<i){
			temp1 = SAMPLE_NUMBER+count-i;
		}else{
			temp1 = count-i;
		}
		if(count<i+1){
			temp2 = SAMPLE_NUMBER+(count-1)-i;
		}else{
			temp2 = (count-1)-i;
		}		
		if(value[temp1]<=value[temp2])return(0);
	}
	if(_valueFlag){
		_valueFlag=1;
		return(0);
	}else{
		_valueFlag=1;
		return(1);
	}	
}

/*!
* @brief Waveform down processing
*
* @brief  When the sample values decreased four times in a row, clear the heartbeat
*
* @return void
*/ 

void DFRobot_Heartrate::minNumber(uint8_t count)
{
	uint16_t temp1,temp2;
	for(int i=0;i<4;i++){
		if(count<i){
			temp1 = SAMPLE_NUMBER+count-i;
		}else{
			temp1 = count-i;
		}
		if(count<i+1){
			temp2 = SAMPLE_NUMBER+(count-1)-i;
		}else{
			temp2 = (count-1)-i;
		}		
		if(value[temp1]>=value[temp2])return;
	}
	_valueFlag = 0;
	
}


/*!
* @brief Get heart rate value
*
* @brief  Sample ten times in a row beating heart rate value is computed
*
* @return uint16_t
*/ 

uint16_t DFRobot_Heartrate::analogGetRate(void)
{

	static uint8_t timeFlag;
	static unsigned long sampleTime[10];
	unsigned long valueTime_;
	minNumber(_valueCount);
	if(maxNumber(_valueCount)){       
        _nowTim = millis();
		uint32_t difTime =  _nowTim - _lastTim;
        _lastTim = _nowTim;
        
        if(difTime>300 || difTime<2000){
            sampleTime[timeFlag++] = difTime;
            if(timeFlag > 9)timeFlag=0;
        }       
        if(0 == sampleTime[9]){
            Serial.println("Wait for valid data !"); 
            return(0);
        }
        		
		uint32_t Arrange[10]={0};		
		for(int i=0;i<10;i++){
            Arrange[i] = sampleTime[i];
        }
        uint32_t Arrange_=0;
        for(int i=9;i>0;i--){
            for(int j=0;j<i;j++){
                if(Arrange[j] > Arrange[j+1]){
                Arrange_ = Arrange[j];
                Arrange[j] = Arrange[j+1];
                Arrange[j+1] = Arrange_;
                }
            }            
        }   
		if((Arrange[7]-Arrange[3])>150){
            Serial.println("Wait for valid data !");  
			return(0);
		}	
        
        Arrange_ = 0;
		for(int i=3;i<=7;i++){
			Arrange_ += Arrange[i];
		}
		
		valueTime_ = 300000/Arrange_;///<60*1000*(7-2)	
		return((uint16_t)valueTime_);
	}	
	return(0);
}

/*!
* @brief Get heart rate value
*
* @brief  Sample ten times in a row beating heart rate value is computed
*
* @return uint16_t
*/ 

uint16_t DFRobot_Heartrate::digitalGetRate(void)
{

	static uint8_t timeFlag;
	static unsigned long sampleTime[10];
	unsigned long valueTime_;
	uint8_t count_;
	
	if(_valueCount){
		count_ = _valueCount-1;
	}else{
		count_ = SAMPLE_NUMBER-1;
	}
	if((value[_valueCount]>1000)&&(value[count_]<20)){       
        nowTim = millis();
		uint32_t difTime =  nowTim - _lastTim;
        _lastTim = nowTim;
        
        if(difTime>300 || difTime<2000){
            sampleTime[timeFlag++] = difTime;
            if(timeFlag > 9)timeFlag=0;
        }       
        if(0 == sampleTime[9]){
            Serial.println("Wait for valid data !"); 
            return(0);
        }
        		
		uint32_t Arrange[10]={0};		
		for(int i=0;i<10;i++){
            Arrange[i] = sampleTime[i];
        }
        uint32_t Arrange_=0;
        for(int i=9;i>0;i--){
            for(int j=0;j<i;j++){
                if(Arrange[j] > Arrange[j+1]){
                Arrange_ = Arrange[j];
                Arrange[j] = Arrange[j+1];
                Arrange[j+1] = Arrange_;
                }
            }            
        }   
		if((Arrange[7]-Arrange[3])>120){
            Serial.println("Wait for valid data !");  
			return(0);
		}	
        
        Arrange_ = 0;
		for(int i=3;i<=7;i++){
			Arrange_ += Arrange[i];
		}
		
		valueTime_ = 300000/Arrange_;///<60*1000*(7-2)	
		return((uint16_t)valueTime_);
    }	
	return(0);

}

/*!
* @brief Get heart rate value
*
* @brief  Sample ten times in a row beating heart rate value is computed
*
* @return uint16_t
*/ 
uint16_t DFRobot_Heartrate::getRate(void)
{
	if(_mode_ == DIGITAL_MODE){
		return(digitalGetRate());
	}else{
		return(analogGetRate());
	}
}



/******************************************************************************
  Copyright (C) <2015>  <linfeng>
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  Contact: Musk.lin@dfrobot.com
 ******************************************************************************/
 

    
