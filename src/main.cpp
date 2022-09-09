#include <Arduino.h>
#include <IMU6050.h>
#include <BARO280.h>
#include <GNC.h>
#include <State_Indication.h>
#include <System.h>
#include <pyro.h>
#include <datalog.h>
#include <TVC.h>
int systemState = 0;
extern float altitudeAGL = 0;
extern int altitude = 0;
extern int temp = 0;
extern int pressure = 0;
void setup()
{
    Serial.begin(9600);
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
    Serial.println(BMPAltitudeUpdateAGL()); // debugging
    if (systemState == 0)                   // Ground idle
    {
        allPyrosLow();
        detectLiftoff();
    }
    if (systemState == 1) // Ascent
    {
        detectApogee();
    }
    if (systemState == 2) // Ballistic descent
    {
        detectChutes();
    }
    if (systemState == 3) // Under chutes
    {
        detectLanding();
    }
    if (systemState == 4)
    {
        stopDataLog();
    }
    delay(10);
}