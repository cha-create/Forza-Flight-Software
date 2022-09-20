#include <Arduino.h>
#include <IMU6050.h>
#include <BARO280.h>
#include <GNC.h>
#include <State_Indication.h>
#include <System.h>
#include <pyro.h>
#include <datalog.h>
#include <TVC.h>
bool errorboi = false;
int systemState = 0;
extern float altitudeAGL = 0;
extern int altitude = 0;
extern int temp = 0;
extern int pressure = 0;
void setup()
{
    Serial.begin(9600);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    mpuInit();
    BMPInit();
    SDInit();
    TVCInitalize();
    delay(500);
    startupBeeps();
    Serial.println("startup complete...");
    delay(250);
}

void loop()
{
    timeKeeper();
    State_Indication();
    navUpdate();
    dataLog();
    TVCCenter();
    Serial.println(timeSinceLiftoff);  // debugging
    if (systemState == 0 && !errorboi) // Ground idle
    {
        allPyrosLow();
        detectLiftoff();
    }
    if (systemState == 1) // Ascent
    {
        if (timeSinceLiftoff >= 4500)
        {
            FirePyro1();
            hitApogee = true;
            systemState++;
        }
    }
    if (systemState == 2) // under chutes
    {
        detectLanding();
    }
    if (systemState == 3) // landed
    {
        stopDataLog();
    }

    delay(10);
}