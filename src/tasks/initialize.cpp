/**
 * @file    initialize.cpp
 * @brief   Code for Initializing the sensors
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void initialize(void *){
  SPI.begin();
  while (true){
    if(SD.begin(BUILTIN_SDCARD) && bmp.begin(BMP_CS)!=-1){
      digitalWrite(SENSOR_CHECK, arduino::HIGH);
      taskENTER_CRITICAL();
      state = ROP;
      xTaskNotifyGive(FSM_tHandle);
      xTaskNotifyGive(get_data_tHandle);
      taskEXIT_CRITICAL();
    }
    else{
      taskENTER_CRITICAL();
      state = FAILURE;
      xTaskNotifyGive(FSM_tHandle);
      taskEXIT_CRITICAL();
    }
  }
}