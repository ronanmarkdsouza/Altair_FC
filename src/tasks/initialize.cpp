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
    tone(BUZZER, 1000);
    if(SD.begin(BUILTIN_SDCARD) && bmp.begin(BMP_CS)!=-1){
      delay(2000);
      noTone(BUZZER);
      digitalWrite(SENSOR_CHECK, arduino::HIGH);
      taskENTER_CRITICAL();
      noTone(BUZZER);
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