/*
Code for the Flight Computer on-board Altair.
This code has been written by thrustMIT 2022-23 for Spaceport America Cup 2023

The following components were used for the Flight Computer:
              - LED1       | Sensor Check
              - LED2       | Telemetry Link
              - LED3       | GPS Fix
              - LED4       | Mishap Indicator
              - Buzzer     | Indication
              - BMP388     | Static Pressure Sensor
              - MPU6050    | Inertial Measurement Unit
              - MPX5100DP  | Differential Pressire Sensor
              - Adafruit   |
                Ultimate   | GPS Coordinates
                GPS        | 
              - XBee Pro   | Data Telemetry
              - D4184      | MOSFET for Parachute Ejection and Reefing
              - MG996      | Servo Motor for actuation of Air Brakes
*/
/**
 * @file    main.cpp
 * @brief   Altair Flight Computer Code
 * @author  Ronan Mark D'souza
 * @date    05.05.2023
 */
#include "arduino_freertos.h"
#include "thrustMIT.h"
#include "../../../Altair_FC/src/tasks.cpp"
#include "../../../Altair_FC/src/states.cpp"
#include <imxrt.h>
#include <SD.h>
#define FILENAME "data.txt"

FLASHMEM __attribute__((noinline)) void setup(){
  Serial.begin(9600);
  
  xTaskCreate(apogee_detection, "Apogee Detection", 512, nullptr, 1, nullptr);
  xTaskCreate(apogee_prediction, "Apogee Prediction", 512, nullptr, 1, nullptr);
  xTaskCreate(data_telemetry, "Data Telemetry", 512, nullptr, 1, nullptr);
  xTaskCreate(data_logging, "Apogee Logging", 512, nullptr, 1, nullptr);
  vTaskStartScheduler();
}

void loop(){}