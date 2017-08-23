#include "UvML8511.h"

UvML8511 uv;

void testHandle(float UvValue)
{

}

void setup()
{
    uv.setPin(A0);
    uv.setup();
    uv.setHandleM(testHandle, 20);
    uv.setHandleL(testHandle, 20);
    Serial.begin(9600);
   
}

void loop()
{
    uv.update();
    Serial.print("UvIntensity: ");
    Serial.println(uv.getUvValue());
    Serial.print("UvVoltageValue: ");
    Serial.println(uv.getVoltageValue());
    
}
