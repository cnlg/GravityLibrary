#ifndef _LIQUIDFLOW_H_
#define _LIQUIDFLOW_H_ 


class LiquidFlow
{
public:
     LiquidFlow();
     ~LiquidFlow();

public:
    double getValue();
    void setInterrupt(uint8_t interruptNum);

};

#endif
