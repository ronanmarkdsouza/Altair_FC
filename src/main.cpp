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
#include "../../../Altair_FC/src/tasks/tasks.h"

Data data_pack;
TaskHandle_t get_dataHandle;
TaskHandle_t apogee_detectionHandle;
TaskHandle_t apogee_predictionHandle;
TaskHandle_t data_telemetryHandle;
TaskHandle_t data_loggingHandle;

FLASHMEM __attribute__((noinline)) void setup(){
  Serial.begin(9600);
  xTaskCreate(get_data, "Get Data", 16384, nullptr, 1, &get_dataHandle);
  xTaskCreate(apogee_detection, "Apogee Detection", 16384, nullptr, 1, &apogee_detectionHandle);
  xTaskCreate(apogee_prediction, "Apogee Prediction", 16384, nullptr, 1, &apogee_predictionHandle);
  xTaskCreate(data_telemetry, "Data Telemetry", 16384, nullptr, 1, &data_telemetryHandle);
  xTaskCreate(data_logging, "Apogee Logging", 16384, nullptr, 1, &data_loggingHandle);
  vTaskStartScheduler();
}

void loop(){}