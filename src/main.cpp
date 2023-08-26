#include <Arduino.h>
#include <IMU6050.h>
#include <BARO280.h>
#include <System.h>
#include <arduino-timer.h>
#include <GNC.h>
#include <State_Indication.h>
#include <pyro.h>
#include <datalog.h>
#include <TVC.h>
int systemState = 0;
Timer<3> timer;
//extern float SITLaltitudeUpdate();
extern float altitudeAGL = 0;
extern int altitude = 0;
extern int temp = 0;
extern int pressure = 0;


void setup()
{
    allPyrosLow();
    Serial.begin(9600);
    delay(3000);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
    mpuInit();
    calibrateGyro();
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
    //checkDataLog();
    navUpdate();
    dataLog();
    TVCCenter();
    getAngle();
    Serial.print(String(timeSinceLiftoff) + ", ");
    Serial.print(String(angleX) + ", " + String(angleY) + ", " + String(angleZ) + ", ");
    Serial.println(systemState);       // debugging
    if (systemState == 0 && !errorboi) // Ground idle
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
    timer.tick();
    delay(10);
}