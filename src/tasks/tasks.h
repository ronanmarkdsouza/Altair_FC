#ifndef TASK_FUNCTIONS_H
#define TASK_FUNCTIONS_H

#include "arduino_freertos.h"
#include <imxrt.h>
#include <SD.h>
#include "thrustMIT.h"
#include <SPI.h> 
#include <BMP388.h>
#include <task.h>
#include <semphr.h>

extern Data data_pack;
extern States state;
extern TaskHandle_t initialize_tHandle;
extern TaskHandle_t get_data_tHandle;
extern TaskHandle_t apogee_detection_tHandle;
extern TaskHandle_t apogee_prediction_tHandle;
extern TaskHandle_t data_telemetry_tHandle;
extern TaskHandle_t data_logging_tHandle;
extern TaskHandle_t failure_tHandle;
extern TaskHandle_t FSM_tHandle;
extern TaskHandle_t stateChangeTaskHandle;
extern TaskHandle_t ROP_tHandle;
extern TaskHandle_t Drogue_out_tHandle;
extern TaskHandle_t kadar_tHandle;
extern BMP388 bmp; 
extern BMP388::BMP388_data bmp_data;
extern SemaphoreHandle_t dataSem;
extern float initial_alt;

void get_data(void*);
void apogee_detection(void*);
void apogee_prediction(void*);
void data_telemetry(void*);
void data_logging(void*);
void initialize(void *);
void failure_t(void *);
void ROP_t(void *);
void drogue_out(void *);
void kadar_rec(void *);
void FSM(void *);

#endif
