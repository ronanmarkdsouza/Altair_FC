/**
 * @file    apogee_detection.cpp
 * @brief   Code for Apogee Detection
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void apogee_detection(void*) {
    while (true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        Serial.print("Apogee Detection --> ");
        Serial.println(data_pack.pitch);
        delay(1000);
    }
}
