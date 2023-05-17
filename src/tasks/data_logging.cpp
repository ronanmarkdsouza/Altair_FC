#include "../../../Altair_FC/src/tasks/tasks.h"

void data_logging(void*){
  while(true){
    Serial.println("Data Logging");
    Serial.println("-------------------------------------");
    delay(1000);
  }
}