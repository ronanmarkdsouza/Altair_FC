/**
 * @file    FSM.cpp
 * @brief   Code for FSM
 * @author  Ronan Mark D'souza
 * @date    18.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

States state = INITIALIZE;
void FSM(void*){
    Serial.println("Running FSM");
    Serial.println("Suspending all tasks except FSM");

    vTaskSuspend(initialize_tHandle);
    vTaskSuspend(get_data_tHandle);
    vTaskSuspend(apogee_detection_tHandle);
    vTaskSuspend(data_logging_tHandle);
    vTaskSuspend(data_telemetry_tHandle);
    vTaskSuspend(failure_tHandle);
    Serial.println("Done Suspending Tasks, entering switch case statement");
    while (true){
        switch (state)
        {
        case INITIALIZE:
        Serial.println("Resuming initialize task");
        vTaskResume(initialize_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        case ROP:
        Serial.println("Suspending Initialize task");
        vTaskSuspend(initialize_tHandle);
        delay(1000);
        Serial.println("Resuming data telemetry tasks");
        delay(1000);
        vTaskResume(data_telemetry_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        case COAST:
        while(true) Serial.println("COAST");
            break;
        case APOGEE:
        while(true) Serial.println("APOGEE");
            break;
        case DESCENT:
        while(true) Serial.println("DESCENT");
            break;
        case DISREEFED:
        while(true) Serial.println("DISREEFED");
            break;
        case TOUCHDOWN:
        while(true) Serial.println("TOUCHDOWN");
            break;
        case FAILURE:
        Serial.println("Suspending all tasks");
        vTaskSuspend(initialize_tHandle);
        Serial.println("Resuming FAILURE state");
        delay(1000);
        vTaskResume(failure_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        default:
            break;
        }
    }
}