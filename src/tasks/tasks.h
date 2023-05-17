#ifndef TASK_FUNCTIONS_H
#define TASK_FUNCTIONS_H

#include "arduino_freertos.h"
#include <Arduino.h>
#include <imxrt.h>
#include <SD.h>
#include "thrustMIT.h"
#include "thrustMIT.h"

extern Data data_pack;
extern TaskHandle_t get_dataHandle;
extern TaskHandle_t apogee_detectionHandle;
extern TaskHandle_t apogee_predictionHandle;
extern TaskHandle_t data_telemetryHandle;
extern TaskHandle_t data_loggingHandle;

void get_data(void*);
void apogee_detection(void*);
void apogee_prediction(void*);
void data_telemetry(void*);
void data_logging(void*);

#endif
