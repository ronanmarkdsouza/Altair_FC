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
TaskHandle_t initialize_tHandle = NULL;
TaskHandle_t get_data_tHandle = NULL;
TaskHandle_t apogee_detection_tHandle = NULL;
TaskHandle_t apogee_prediction_tHandle = NULL;
TaskHandle_t data_telemetry_tHandle = NULL;
TaskHandle_t data_logging_tHandle = NULL;
TaskHandle_t failure_tHandle = NULL;
TaskHandle_t FSM_tHandle = NULL;

BMP388 bmp; 
BMP388::BMP388_data bmp_data;

FLASHMEM __attribute__((noinline)) void setup()
{
  Serial.begin(9600);
  GPS_SERIAL.begin(9600);
  pinMode(MAIN, arduino::OUTPUT);
  pinMode(DROGUE, arduino::OUTPUT);
  pinMode(BUZZER, arduino::OUTPUT);
  pinMode(MISHAP, arduino::OUTPUT);
  pinMode(SENSOR_CHECK, arduino::OUTPUT);
  xTaskCreate(FSM, "FSM", 8192, nullptr, 1, &FSM_tHandle);
  xTaskCreate(initialize, "Initialize", 8192, nullptr, 1, &initialize_tHandle);
  xTaskCreate(get_data, "Get Data", 8192, nullptr, 1, &get_data_tHandle);
  xTaskCreate(apogee_detection, "Apogee Detection", 8192, nullptr, 1, &apogee_detection_tHandle);
  xTaskCreate(data_telemetry, "Data Telemetry", 8192, nullptr, 1, &data_telemetry_tHandle);
  xTaskCreate(data_logging, "Data Logging", 8192, nullptr, 1, &data_logging_tHandle);
  xTaskCreate(failure_t, "Failure", 8192, nullptr, 1, &failure_tHandle);
  vTaskStartScheduler();
}

void loop() {}