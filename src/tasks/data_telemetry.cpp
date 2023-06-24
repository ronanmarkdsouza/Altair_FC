/**
 * @file    data_telemetry.cpp
 * @brief   Code for Data Telemetry
 * @author  Ronan Mark D'souza
 * @date    17.05.2023
 */
#include "../../../Altair_FC/src/tasks/tasks.h"
#include <string.h>

uint8_t destAddress[] = { 0x00, 0x13, 0xA2, 0x00, 0x41, 0x03, 0x63, 0xD5 };  // Destination address

uint8_t packet[256];

void createXBeePacket(uint8_t* destAddress, String data, uint16_t length, uint8_t* packet) {
  uint8_t checksum = 0;
  packet[0] = 0x7E;
  packet[1] = (length + 13) >> 8; // MSB, Adjust the length to include the destination address and other packet overhead
  packet[2] = (length + 13) & 0xFF; // LSB
  packet[3] = 0x10; // Transmit Request
  packet[4] = 0x01; // Set a unique ID for each packet
  memcpy(packet + 5, destAddress, 8);
  packet[13] = 0xFF;
  packet[14] = 0xFE;
  packet[15] = 0x00;
  packet[16] = 0x00;

  // memcpy(packet + 17, data, length);

    for (uint16_t i = 0; i < data.length(); i++) {
    packet[i + 17] = data[i];
  }

  for (int i = 3; i < length + 16; i++) {
    checksum += packet[i];
  }
  checksum = 0xFF - checksum;

  packet[length + 16] = checksum;
}

void data_telemetry(void*){
  digitalWrite(TEL_LINK, arduino::HIGH);
  while(true){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    unsigned long elapsedMillis = millis();

  // Calculate minutes and seconds
  unsigned int minutes = (elapsedMillis / 60000) % 60;
  unsigned int seconds = (elapsedMillis / 1000) % 60;

    String data1 = String(minutes);
    String data2 = String(seconds);
    String data3 = String(data_pack.vel,3);
    String data4 = String(data_pack.alt-initial_alt, 3);
    String data5 = String(data_pack.pres, 3);
    String data6 = String(data_pack.lat, 4);
    String data7 = String(data_pack.lon, 4);
    String data = data3+ "," + data4+ "," + data5+ "," + data6+ "," + data7;
    // data1 + ":" + data2 + "," + 
    uint16_t length = data.length(); 
    createXBeePacket(destAddress, data, length, packet);
    for (int i = 0; i < length+17; i++) {
    XB_SERIAL.write(packet[i]);
    }
    delay(5);
  }
}
