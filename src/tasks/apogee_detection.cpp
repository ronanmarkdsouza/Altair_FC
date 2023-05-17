#include "../../../Altair_FC/src/tasks/tasks.h"

void apogee_detection(void*) {
    while (true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        Serial.print("Apogee Detection --> ");
        Serial.println(data_pack.pitch);
        delay(1000);
    }
}
