#include <Arduino.h>
#include <SD.h>

File forzaFlightData;
const char filename[] = "forzaDataLog.txt";
extern float pressure;
extern float temp;
extern float altitude;
extern float maxAltitude;
extern bool pyro1Fired;
extern int servoxAngle;
extern int servozAngle;
extern double setpoint;
extern double xoutput;
extern double zoutput;
char buffer[512];
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

            forzaFlightData.println("Time, X_ACC, Y_ACC, Z_ACC, X_GYRO, Y_GYRO, Z_GYRO, Yaw, Pitch, Roll, Serv_Angle_X, Serv_Angle_Z, System_State, altitude, altitudeAGL, Pressure, Temp, pyro1Fired, pyroActive, timeSinceLiftoff, setpoint, xPIDOutput, zPIDOutput");
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
            sprintf(buffer, "%lu,%d,%d,%d,%d,%d,%d,%f,%f,%f,%d,%d,%d,%f,%f,%f,%f,%d,%d,%d,%f,%f,%f", millis(), ax, ay, az, gx, gy, gz, angleZ, angleX, angleY, servoxAngle, servozAngle, systemState, BMPAltitudeUpdate(), BMPAltitudeUpdateAGL(), BMPPressureUpdate(), BMPTempUpdate(), pyro1Fired, pyroActive,  timeSinceLiftoff, setpoint, xoutput, zoutput);
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