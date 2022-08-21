#include <Arduino.h>
#include <SD.h>

File forzaFlightData;
const char filename[] = "forzaDataLog.txt";
extern int pressure;
extern int temp;
extern int altitude;
char buffer[128];
bool hasRun = false;
void SDInit()
{
    SD.begin(BUILTIN_SDCARD);
    if (!SD.begin(BUILTIN_SDCARD))
    {
        Serial.print("The SD card failed to initalize");
        while (1)
            ;
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

            forzaFlightData.println("Time, X_ACC, Y_ACC, Z_ACC, X_GYRO, Y_GYRO, Z_GYRO, System_State, altitude, altitudeAGL, Pressure, Temp");
        }
        hasRun = true;
    }
    forzaFlightData.close();
}

void dataLog()
{
    forzaFlightData = SD.open(filename, FILE_WRITE);
    if (forzaFlightData)
    {
        sprintf(buffer, "%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f,%f", millis(), ax, ay, az, gx, gy, gz, systemState, BMPAltitudeUpdate(), BMPAltitudeUpdateAGL(), BMPPressureUpdate(), BMPTempUpdate());
        forzaFlightData.println(buffer);
        // Serial.println(millis()); // just a lil debugging :)
        delay(100);
    }
    forzaFlightData.close();
}
void stopDataLog()
{
    forzaFlightData.close();
}