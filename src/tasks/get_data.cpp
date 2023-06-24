/**
 * @file    get_data.cpp
 * @brief   Code for Reading data from sensors
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"

//Function to get altitude
float estimate_altitude(float pressure, float temperature){
  float altitude = ((pow(101325/pressure,1/5.257) - 1) * (temperature + 273.15))/0.0065; 
  return altitude;
}

float get_velocity(int analog1, int analog2, float pres, float temp){
  float v_out1 = analogRead(analog1)*5.0/1023.0;
  float v_out2 = analogRead(analog2)*5.0/1023.0;
  float rho = pres/(287.05*temp);
  float v_out = 0;

  if(abs(v_out1-v_out2)>10)
    v_out = max(v_out1, v_out2);
  else
    v_out = (v_out1+v_out2)/2;

  float pitot_pressure = (v_out - 0.8)/0.18;
  return sqrt((16*pitot_pressure*1000)/rho);
}

void get_data(void*){
  float prev_alt = 0.0;
  while(true){
    bmp.get_new_data(&bmp_data);
    float altitude = estimate_altitude(bmp_data.pressure, bmp_data.temperature);
    data_pack.alt = altitude;
    data_pack.vel = (altitude - initial_alt - prev_alt)/0.01;
    float prev_alt = altitude;
    data_pack.pres = bmp_data.pressure;
    data_pack.lat = 32.320540;
    data_pack.lon = -106.748230;
    xTaskNotifyGive(data_logging_tHandle);
    xTaskNotifyGive(data_telemetry_tHandle);
    delay(10);
  }
}