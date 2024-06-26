#include <Arduino.h>
#include <SD.h>

File forzaFlightData;
const char filename[] = "forzaDataLog.txt";
extern int pressure;
extern int temp;
extern int altitude;
extern float maxAltitude;
extern bool pyro1Fired;
extern int servoxAngle;
extern int servozAngle;
char buffer[128];
bool hasRun = false;
void SDInit()
{
    SD.begin(BUILTIN_SDCARD);
    if (!SD.begin(BUILTIN_SDCARD))
    {
        Serial.print("The SD card failed to initialize");
        failureBeeps();
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

            forzaFlightData.println("Time, X_ACC, Y_ACC, Z_ACC, X_GYRO, Y_GYRO, Z_GYRO, Yaw, Pitch, Roll, Serv_Angle_X, Serv_Angle_Z, System_State, altitude, altitudeAGL, Pressure, Temp, pyro1Fired, pyroActive, timeSinceLiftoff");
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
        forzaFlightData = SD.open(filename, FILE_WRITE);
        if (forzaFlightData)
        {
            sprintf(buffer, "%d,%d,%d,%d,%d,%d,%d,%f,%f,%f,%d,%d,%d,%f,%f,%f,%f,%d,%d,%d", millis(), ax, ay, az, gx, gy, gz, angleZ, angleX, angleY, servoxAngle, servozAngle, systemState, BMPAltitudeUpdate(), BMPAltitudeUpdateAGL(), BMPPressureUpdate(), BMPTempUpdate(), pyro1Fired, pyroActive,  timeSinceLiftoff);
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
    forzaFlightData.close();
}
void stopDataLog()
{
    forzaFlightData.close();
}