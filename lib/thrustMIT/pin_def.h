#ifndef PIN_DEF_H
#define PIN_DEF_H

//Indicator LEDs
#define SENSOR_CHECK 37 //LED indicator if all sensors are functioning properly
#define TEL_LINK 33 //To determine whether there is a link in telemetry with the ground station
#define GPS_FIX 36 //Indicator for the GPS Fix
#define MISHAP 22 //Indicator for malfunctioning sensors with code to identify sensor
#define BUZZER 28 //Indicator for events and malfunctions

//Peripherals
#define BMP_SCK 13
#define BMP_SDI 11
#define BMP_SDO 12 
#define BMP_CS 10
#define MPU_SDA 18
#define MPU_SCL 19
#define MPX_1 14
#define MPX_2 15 
#define GPS_RX 17
#define GPS_TX 16
#define XB_RX 8
#define XB_TX 7
#define XB_RSSI 2
#define MAIN 25
#define DROGUE 24 
#define AIR_BRAKES 23
#define GPS_SERIAL Serial4
#define XB_SERIAL Serial2

#endif