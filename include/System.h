#include <Arduino.h>
#include <Adafruit_BMP280.h>
unsigned long currentMillis;
extern int systemState;
extern int16_t ay;
extern int16_t ax;
int timeSinceLiftoff;
bool hasrun = false;
bool hasrun1 = false;
void timeKeeper()
{
    if (systemState >= 1)
    {
        int onTime = millis();
        if (hasrun1 == false)
        {
            currentMillis = millis();
            hasrun1 = true;
        }
        if (systemState >= 1)
        {
            timeSinceLiftoff = onTime - currentMillis;
            if (hasrun == false)
            {
                currentMillis = onTime;
                hasrun = true;
            }
        }
    }
}
