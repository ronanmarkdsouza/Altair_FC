/**
 * @file    ROP.cpp
 * @brief   Code for Initializing the sensors
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void ROP_beep(){
    noTone(BUZZER);
    delay(1000);
    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
    delay(100);
    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
    delay(100);
    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
}
void ROP_t(void *){
  initial_alt = data_pack.alt;
  while (true){
    // Serial.print("0.0,");
    Serial.println(data_pack.alt-initial_alt);
    // Serial.println(",0.0,32.3250,-106.7482");
    ROP_beep();

    if(data_pack.alt-initial_alt >500.0){
      noTone(BUZZER);
      taskENTER_CRITICAL();
      state = ARMED;
      xTaskNotifyGive(FSM_tHandle);
      xTaskNotifyGive(get_data_tHandle);
      taskEXIT_CRITICAL();
    }
  }
}