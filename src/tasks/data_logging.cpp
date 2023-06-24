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
    String data3 = String(data_pack.alt,3);
    String data4 = String(data_pack.alt-initial_alt, 3);
    String data5 = String(data_pack.pres, 3);
    String data6 = String(data_pack.lat, 4);
    String data7 = String(data_pack.lon, 4);
    String data = data3+ "," + data4+ "," + data5+ "," + data6+ "," + data7;
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    File file = SD.open("data.csv", FILE_WRITE);
  if (file) {
    file.println(data);
    file.close();
  }
  delay(100);
  }
}