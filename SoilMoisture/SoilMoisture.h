#ifndef _SoilMoisture_H_
#define _SoilMoisture_H_

typedef void (*HandleFunc)(int smValue);

class SoilMoisture
{
    public:
        SoilMoisture();
        ~SoilMoisture();
    
    public:
        void setPin(int pin);
        void setAirWaterValue(int airValue, int waterValue); 
        void setup();
        void update();
        int  getValue();
        void setHandleVeryWet(HandleFunc handleVeryWet);
        void setHandleWet(HandleFunc handleWet);
        void setHandleDry(HandleFunc handleDry);

    private:
        HandleFunc _handleVeryWet;
        HandleFunc _handleWet;
        HandleFunc _handleDry;
        unsigned long _currentTime;
        int _soilMoistureValue;
        int _airValue;   //you need to replace this value with Value_1
        int _waterValue;  //you need to replace this value with Value_2
        int _intervals;   
        int _pin;

};

#endif
