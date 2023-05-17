/**
 * @file    data_logging.cpp
 * @brief   Code for Data Logging on the Teensy 4.1
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void data_logging(void*){
  while(true){
    Serial.println("Data Logging");
    Serial.println("-------------------------------------");
    delay(1000);
  }
}