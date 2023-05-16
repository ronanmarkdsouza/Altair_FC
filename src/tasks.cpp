#include <Arduino.h>
static void apogee_detection(void*){
  while(true){
    Serial.println("Apogee Detection");
  }
}

static void apogee_prediction(void*){
  while(true){
    Serial.println("Apogee Prediction");
  }
}

static void data_telemetry(void*){
  while(true){
    Serial.println("Data Telemetry");
  }
}

static void data_logging(void*){
  while(true){
    Serial.println("Data Logging");
  }
}