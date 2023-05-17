/**
 * @file    get_data.cpp
 * @brief   Code for Reading data from sensors
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void get_data(void*){
  //Implement the code for collecting the data from the sensors here and also send the data to all the other tasks
  while(true){
  //Acquire data
    taskENTER_CRITICAL();
    data_pack.alt = 10.2;
    data_pack.vel = 10.2;
    data_pack.pres = 10.2;
    data_pack.ax = 10.2;
    data_pack.ay = 10.2;
    data_pack.az = 10.2;
    data_pack.roll = 10.2;
    data_pack.pitch = 10.2;
    data_pack.yaw = 10.2;
    taskEXIT_CRITICAL();

    xTaskNotifyGive(apogee_detectionHandle);
    xTaskNotifyGive(apogee_predictionHandle);
    xTaskNotifyGive(data_telemetryHandle);
    xTaskNotifyGive(data_loggingHandle);

  }
}