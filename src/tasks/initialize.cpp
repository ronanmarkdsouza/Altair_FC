/**
 * @file    initialize.cpp
 * @brief   Code for Initializing the sensors
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"
void initialize(void *){
  while (true){
    if(!true){
      taskENTER_CRITICAL();
      state = ROP;
      taskEXIT_CRITICAL();
      xTaskNotifyGive(FSM_tHandle);
    }
    else{
      taskENTER_CRITICAL();
      state = FAILURE;
      taskEXIT_CRITICAL();
      xTaskNotifyGive(FSM_tHandle);
    }
    delay(1000);
  }
}