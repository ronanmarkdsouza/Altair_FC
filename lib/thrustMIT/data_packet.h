#ifndef DATA_PACKET_H
#define DATA_PACKET_H

struct Data{
    String time_stamp;
    float alt;
    float vel;
    float pres;
    float ax;
    float ay;
    float az;
    float roll;
    float pitch;
    float yaw;
};

#endif