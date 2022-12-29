#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <Wire.h>
#include <UniversalTimer.h>
#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)
Adafruit_BMP280 bmp(BMP_CS);
UniversalTimer deviationDelay(5000, false);
extern int systemState;
extern void failureBeeps();
bool hitApogee;
bool hasDeviation;
extern int timeSinceLiftoff;
extern float altitudeAGL;
int deviation;
float currentAltitude = 0;
void BMPInit()
{
    if (!bmp.begin())
    {
        Serial.print("Connection To Barometer Failed...");
        failureBeeps();
    }
    Serial.println("Succesfully connected to BMP280.");
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,  /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,  /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16, /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,   /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_1);
}

void printVals_BARO_x10()
{
    for (int i = 0; i < 10; i++)
    {
        Serial.println(bmp.readAltitude(1017.0));
        delay(500);
    }
}

float BMPPressureUpdate()
{
    return bmp.readPressure();
}
float BMPTempUpdate()
{
    return bmp.readTemperature();
}
float BMPAltitudeUpdate()
{
    return bmp.readAltitude(1013.55); // Adjust to local forecast!!
}
float BMPAltitudeUpdateAGL()
{
    if (systemState < 1)
    {
        deviationDelay.start();
        if (deviationDelay.check() && !hasDeviation)
        {
            deviation = bmp.readAltitude(1013.55);
            Serial.println("deviation logged");
            hasDeviation = true;
        }
        altitudeAGL = deviation - deviation;
        return altitudeAGL / 3.281;
    }
    if (systemState >= 1)
    {
        altitudeAGL = bmp.readAltitude(1013.55) - deviation;
        return altitudeAGL / 3.281;
    }
}
bool detectApogee()
{
    if (systemState == 1 && timeSinceLiftoff >= 2500)
    {
        float lastAltitude = currentAltitude;
        currentAltitude = BMPAltitudeUpdateAGL();
        if (currentAltitude > lastAltitude - 0.2)
        {
            return false;
        }
        else
        {
            systemState++;
            hitApogee = true;
            return true;
        }
    }
}
void detectLanding()
{
    if (systemState == 2 && hitApogee && BMPAltitudeUpdateAGL() < 2)
    {
        systemState++;
    }
}