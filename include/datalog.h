#include <Arduino.h>
#include <SD.h>

File forzaFlightData;
const char filename[] = "forzaDataLog.txt";
extern int pressure;
extern int temp;
extern int altitude;
extern bool pyro1Fired;
char buffer[128];
bool hasRun = false;
bool isDataLog = true;
void SDInit()
{
    SD.begin(BUILTIN_SDCARD);
    if (!SD.begin(BUILTIN_SDCARD))
    {
        Serial.print("The SD card failed to initialize");
        failureBeeps();
    }
    Serial.println("The SD card has been initalized.");
    if (SD.exists(filename))
    {
        SD.remove(filename);
    }
    forzaFlightData = SD.open(filename, FILE_WRITE);
    if (!hasRun)
    {
        if (forzaFlightData)
        {

            forzaFlightData.println("Time, X_ACC, Y_ACC, Z_ACC, X_GYRO, Y_GYRO, Z_GYRO, System_State, altitude, altitudeAGL, Pressure, Temp, pyro1Fired, timeSinceLiftoff");
        }
        hasRun = true;
    }
    forzaFlightData.close();
}

void dataLog()
{
    if (isDataLog)
    {
        forzaFlightData = SD.open(filename, FILE_WRITE);
        if (forzaFlightData)
        {
            sprintf(buffer, "%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%d, %d", millis(), ax, ay, az, gx, gy, gz, systemState, BMPAltitudeUpdate(), BMPAltitudeUpdateAGL(), BMPPressureUpdate(), BMPTempUpdate(), pyro1Fired, timeSinceLiftoff);
            forzaFlightData.println(buffer);
            // Serial.println(millis()); // just a lil debugging :)
            delay(10);
        }
        forzaFlightData.close();
    }
    else
    {
        forzaFlightData.close();
    }
}

void checkDataLog()
{
    if (systemState == 3)
    {
        isDataLog = false;
    }
}