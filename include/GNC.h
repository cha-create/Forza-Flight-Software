#include <Arduino.h>

void navUpdate()
{
    int altitude = BMPAltitudeUpdate();
    int pressure = BMPPressureUpdate();
    int temp = BMPTempUpdate();
    int ax, ay, az = IMUAccelUpdate();
    int gx, gy, gz = IMUGyroUpdate();
    int altitudeAGL = BMPAltitudeUpdateAGL();
}
