/**
 * @file    apogee_detection.cpp
 * @brief   Code for Apogee Detection
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void blink_beep(){
    tone(BUZZER, 1000);
    digitalWrite(GPS_FIX, arduino::HIGH);
    delay(25);
    noTone(BUZZER);
    digitalWrite(GPS_FIX, arduino::LOW);
    delay(25);
}
void apogee_detection(void*) {
    while (true) {
        blink_beep();
        Serial.println(data_pack.alt - initial_alt);        
    }
}
