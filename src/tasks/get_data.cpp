/**
 * @file    get_data.cpp
 * @brief   Code for Reading data from sensors
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

//Function to get altitude
float estimate_altitude(float pressure, float temperature){
  float altitude = ((pow(101325/pressure,1/5.257) - 1) * (temperature + 273.15))/0.0065; 
  return altitude;
}

void get_data(void*){
  while(true){
    bmp.get_new_data(&bmp_data);
    float altitude = estimate_altitude(bmp_data.pressure, bmp_data.temperature);
    data_pack.alt = altitude;
    xTaskNotifyGive(data_logging_tHandle);
    xTaskNotifyGive(data_telemetry_tHandle);
    delay(10);
  }
}