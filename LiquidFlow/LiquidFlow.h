#ifndef _LIQUIDFLOW_H_
#define _LIQUIDFLOW_H_ 


class LiquidFlow
{
public:
     LiquidFlow();
     ~LiquidFlow();

public:
    void setPin(int pin);
    void setup();
    void update();
    double getValue();
    void setInterrupt(uint8_t interruptNum);

private:
    int _pin;
};

#endif
