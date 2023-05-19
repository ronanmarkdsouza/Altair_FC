/**
 * @file    failure.cpp
 * @brief   Code for failure detection
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

void failure_t(void *){
    while(true){
        Serial.println("Failure");
        delay(1000);
    }
}