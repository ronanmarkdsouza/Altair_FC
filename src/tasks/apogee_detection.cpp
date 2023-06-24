/**
 * @file    apogee_detection.cpp
 * @brief   Code for Apogee Detection
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

const int numConsecutiveNegative = 5;  // Number of consecutive negative altitude changes to detect apogee

int altitudeHistory[numConsecutiveNegative];  // Array to store the recent altitude changes
int apogeeDetected = 0;  

void blink_beep(){
    tone(BUZZER, 1000);
    digitalWrite(GPS_FIX, arduino::HIGH);
    delay(25);
    noTone(BUZZER);
    digitalWrite(GPS_FIX, arduino::LOW);
    delay(25);
}

int counter = 0;
float prev_alt = 100;

void apogee_detection(void*) {
    while (true) {
        blink_beep();
        float cur_alt = data_pack.alt;
        
        if(cur_alt-prev_alt<0){
            prev_alt = cur_alt;
            counter++;
        }
            
        else{
            prev_alt = cur_alt;
            counter = 0;
        }

        switch(counter){
            case 15:
                digitalWrite(DROGUE, arduino::HIGH);
                tone(BUZZER, 1000);
                delay(1000);
                noTone(BUZZER);
                digitalWrite(DROGUE, arduino::LOW);
                taskENTER_CRITICAL();
                state = DROGUE_OUT;
                xTaskNotifyGive(FSM_tHandle);
                xTaskNotifyGive(get_data_tHandle);
                taskEXIT_CRITICAL();
                break;
            default:
                continue;
        }
    }
}
