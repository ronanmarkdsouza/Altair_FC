/**
 * @file    data_logging.cpp
 * @brief   Code for Data Logging on the Teensy 4.1
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void data_logging(void*){
    if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  while(true){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    Serial.println("Data Logging");
  // open file for writing
  File file = SD.open("data.bin", FILE_WRITE);

  // write struct to file
  if (file) {
    file.write((uint8_t*)&data_pack, sizeof(data_pack));
    file.close();
  }
  delay(1000);
  }
}