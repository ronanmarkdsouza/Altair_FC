/**
 * @file    drogue_out.cpp
 * @brief   Code for Apogee Detection
 * @author  Ronan Mark D'souza
 * @date    23.06.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void drogue_out(void*) {
    while (true) {
        
        float cur_alt = data_pack.alt-initial_alt;
        Serial.println(cur_alt);
        if(cur_alt<=500.0){
            digitalWrite(MAIN, arduino::HIGH);
            tone(BUZZER, 1000);
            delay(1000);
            noTone(BUZZER);
            digitalWrite(MAIN, arduino::OUTPUT);

            taskENTER_CRITICAL();
            state = RECOVERED;
            xTaskNotifyGive(FSM_tHandle);
            xTaskNotifyGive(get_data_tHandle);
            taskEXIT_CRITICAL();
        }
    }
}
