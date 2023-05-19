/**
 * @file    get_data.cpp
 * @brief   Code for Reading data from sensors
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void get_data(void*){
  while(true){
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    String time_stamp = asctime(gmtm);
    
    taskENTER_CRITICAL();
    data_pack.time_stamp = time_stamp;
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

    xTaskNotifyGive(apogee_detection_tHandle);
    xTaskNotifyGive(apogee_prediction_tHandle);
    xTaskNotifyGive(data_telemetry_tHandle);
    xTaskNotifyGive(data_logging_tHandle);

  }
}