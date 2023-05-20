/**
 * @file    FSM.cpp
 * @brief   Code for FSM
 * @author  Ronan Mark D'souza
 * @date    18.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

States state = INITIALIZE;
void FSM(void*){
    vTaskSuspend(initialize_tHandle);
    vTaskSuspend(get_data_tHandle);
    vTaskSuspend(apogee_detection_tHandle);
    vTaskSuspend(data_logging_tHandle);
    vTaskSuspend(data_telemetry_tHandle);
    vTaskSuspend(failure_tHandle);
    while (true){
        switch (state)
        {
        case INITIALIZE:
        Serial.println("Resuming initialize task");
        vTaskResume(initialize_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        case ROP:
        vTaskResume(get_data_tHandle);
        vTaskResume(apogee_detection_tHandle);
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
        vTaskResume(failure_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        default:
            break;
        }
    }
}