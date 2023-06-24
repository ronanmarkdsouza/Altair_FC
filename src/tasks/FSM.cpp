/**
 * @file    FSM.cpp
 * @brief   Code for FSM
 * @author  Ronan Mark D'souza
 * @date    18.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

States state = INITIALIZE;

void initialize_beep(){
    tone(BUZZER, 1000);
    delay(50);
    noTone(BUZZER);
    delay(50);
    tone(BUZZER, 1000);
    delay(50);
    noTone(BUZZER);
    delay(50);
    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
}
void FSM(void*){
    vTaskSuspend(initialize_tHandle);
    vTaskSuspend(get_data_tHandle);
    vTaskSuspend(apogee_detection_tHandle);
    vTaskSuspend(data_logging_tHandle);
    vTaskSuspend(data_telemetry_tHandle);
    vTaskSuspend(failure_tHandle);
    vTaskSuspend(ROP_tHandle);
    vTaskSuspend(Drogue_out_tHandle);
    vTaskSuspend(kadar_tHandle);
    while (true){
        switch (state)
        {
        case INITIALIZE:
        Serial.println("Resuming initialize task");
        vTaskResume(initialize_tHandle);
        delay(1000);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        case ROP:
        vTaskSuspend(initialize_tHandle);
        vTaskResume(get_data_tHandle);
        vTaskResume(data_telemetry_tHandle);
        vTaskResume(data_logging_tHandle);
        vTaskResume(ROP_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        case ARMED:
        vTaskSuspend(ROP_tHandle);
        vTaskResume(apogee_detection_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        case DROGUE_OUT:
            vTaskSuspend(apogee_detection_tHandle);
            vTaskResume(Drogue_out_tHandle);
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;
        case RECOVERED:
        vTaskSuspend(Drogue_out_tHandle);
        Serial.println("Recovered.");
        vTaskResume(kadar_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        break;
        case FAILURE:
        vTaskResume(failure_tHandle);
        vTaskSuspend(initialize_tHandle);
        vTaskSuspend(get_data_tHandle);
        vTaskSuspend(apogee_detection_tHandle);
        vTaskSuspend(data_logging_tHandle);
        vTaskSuspend(data_telemetry_tHandle);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            break;

        default:
            break;
        }
  }
}