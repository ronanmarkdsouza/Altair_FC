/**
 * @file    failure.cpp
 * @brief   Code for failure detection
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void failure_t(void *){
    while(true){
        digitalWrite(SENSOR_CHECK, arduino::LOW);
        digitalWrite(MISHAP, arduino::HIGH);
        tone(BUZZER, 1000);
        delay(250);
        digitalWrite(MISHAP, arduino::LOW);
        noTone(BUZZER);
        delay(250);
    }
}