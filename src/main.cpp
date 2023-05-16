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
#include <imxrt.h>
#include <SD.h>
#define FILENAME "data.txt"

DATA data = {1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 1.1};

static void task1(void*){
  while(true){
    if (!SD.begin(BUILTIN_SDCARD)) {
      while(1)
    Serial.println("SD initialization failed!");
  }
     File file = SD.open("data.txt", FILE_WRITE);

  // write struct to file
  if (file) {
    file.write((uint8_t*)&data, sizeof(data));
    file.close();
  }
  }
}

FLASHMEM __attribute__((noinline)) void setup(){
  Serial.begin(9600);
  
  xTaskCreate(task1, "task1", 512, nullptr, 1, nullptr);
  vTaskStartScheduler();
}

void loop(){}