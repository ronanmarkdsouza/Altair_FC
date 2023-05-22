/**
 * @file    apogee_detection.cpp
 * @brief   Code for Apogee Detection
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void apogee_detection(void*) {
    while (true) {
        Serial.println(data_pack.alt);
        delay(1000);
    }
}
