/**
 * @file    get_data.cpp
 * @brief   Code for Reading data from sensors
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

float estimate_altitude(float pressure, float temperature){
  float altitude = ((pow(101325/pressure,1/5.257) - 1) * (temperature + 273.15))/0.0065; 
  return altitude;
}

void get_data(void*){
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  while(true){
    bmp.get_new_data(&bmp_data);
    float altitude = estimate_altitude(bmp_data.pressure, bmp_data.temperature);
    taskENTER_CRITICAL();
    data_pack.alt = altitude;
    data_pack.vel = 10.2;
    data_pack.pres = 10.2;
    data_pack.ax = 10.2;
    data_pack.ay = 10.2;
    data_pack.az = 10.2;
    data_pack.roll = 10.2;
    data_pack.pitch = 10.2;
    data_pack.yaw = 10.2;
    taskEXIT_CRITICAL();
  }
}