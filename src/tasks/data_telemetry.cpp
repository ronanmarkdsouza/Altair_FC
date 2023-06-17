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

void createXBeePacket(uint8_t* destAddress, char* data, uint16_t length, uint8_t* packet) {
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

  memcpy(packet + 17, data, length);

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
    int length = snprintf(nullptr, 0, "%f", data_pack.alt-initial_alt) + 1; // Determine required size
    char* data = new char[length]; // Allocate memory dynamically
    snprintf(data, length, "%f", data_pack.alt-initial_alt); // Convert float to char array

    createXBeePacket(destAddress, data, length, packet);
    for (int i = 0; i < length+17; i++) {
    XB_SERIAL.write(packet[i]);
    }
    delay(100);
  }
}
