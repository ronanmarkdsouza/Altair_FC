/*
Library to interface with the BMP388 Pressure Sensor over SPI 

Currently only support SPI (although I2C should be fairly easy to implement) as I have no means 
to test over I2C. 

Author: Jeremy Dunne
Date: 6/15/2020 

*/ 


#ifndef _BMP388_H_
#define _BMP388_H_

#include <Arduino.h> 
#include <SPI.h> 
#include <BMP388_defs.h> 


// settings 
enum BMP388_TEMP_OVERSAMPLING{
    BMP388_TEMP_OVERSAMPLE_X1 = 0x00, 
    BMP388_TEMP_OVERSAMPLE_X2 = 0x01, 
    BMP388_TEMP_OVERSAMPLE_X4 = 0x02,
    BMP388_TEMP_OVERSAMPLE_X8 = 0x03,
    BMP388_TEMP_OVERSAMPLE_X16 = 0x04,
    BMP388_TEMP_OVERSAMPLE_X32 = 0x05
}; 

enum BMP388_PRESSURE_OVERSAMPLING{
    BMP388_PRESSURE_OVERSAMPLE_X1 = 0x00, 
    BMP388_PRESSURE_OVERSAMPLE_X2 = 0x01, 
    BMP388_PRESSURE_OVERSAMPLE_X4 = 0x02,
    BMP388_PRESSURE_OVERSAMPLE_X8 = 0x03,
    BMP388_PRESSURE_OVERSAMPLE_X16 = 0x04,
    BMP388_PRESSURE_OVERSAMPLE_X32 = 0x05
}; 

class BMP388{
public: 
    /**
     * struct for getting data from the BMP388 
     */ 
    struct BMP388_data{
        float pressure; // Pa 
        float temperature; // deg C 
        unsigned long timestamp; // millis 
    }; 

    /** 
     * initialization function 
     * @param cs_pin chip select pin 
     * @return 0 for success, -1 for error
     */ 
    int begin(int cs_pin); 

    /**
     * read new data from the sensor  
     * @param data struct to store data in 
     * @return 0 for success, -1 for error, 1 for no new data 
     */ 
    int get_new_data(BMP388_data *data); 

private: 
    /**
     * Struct for containing all necessary calibration data 
     * Used to calibrate pressure and temperature readings from the sensor 
     */ 
    struct BMP388_calibration_data {
        double par_p11; 
        double par_p10; 
        double par_p9; 
        double par_p8; 
        double par_p7; 
        double par_p6;
        double par_p5;
        double par_p4;   
        double par_p3;
        double par_p2;  
        double par_p1;  
        double par_t3;  
        double par_t2;  
        double par_t1;  
    
    }; 

    // private global variables 
    BMP388_data cur_data; 
    BMP388_calibration_data calib_data; 
    int cs_pin; 
    SPISettings spi_settings; 

    // functions 

    /**
     * read all data from the sensor 
     * @return 0 for success, -1 for failure 
     */ 
    int read_all(); 

    /**
     * compensate the temperature using the calibration data provided 
     * @param uncomp_temp temperature as read from the device 
     * @return temperature, in c 
     */ 
    float compensate_temperature(uint32_t uncomp_temp); 

    /**
     * compensate the pressure using the calibration data provided 
     * @param uncomp_pressure pressure as read from the device 
     * @param comp_temperatuer compensated temperature 
     * @return pressure, in pa  
     */ 
    float compensate_pressure(uint32_t uncomp_pressure, float comp_temperature); 

    /**
     * check for errors reported by the device 
     * @return 0 for no errors, -1 for none 
     */ 
    int check_errors(); 

    /**
     * get calibration data from the device 
     * @return 0 for success, -1 for failure 
     */ 
    int get_calibration_data(); 

    /**
     * check if data is ready 
     * @return 0 for data ready, -1 for no data ready 
     */ 
    int check_data_ready(); 

    /**
     * put the sensor into normal mode 
     * @return 0 for success, -1 for failure 
     */ 
    int enable_normal_mode(); 

    /**
     * enable the pressure and temperature sensors 
     * @return 0 for success, -1 for failure 
     */ 
    int enable_sensors(); 

    /**
     * set the pressure oversampling 
     * @param oversample oversampling rate 
     * @return 0 for success, -1 for failure 
     */ 
    int set_pressure_oversample(BMP388_PRESSURE_OVERSAMPLING oversample); 
    
    
    /**
     * set the temperature oversampling 
     * @param oversample oversampling rate 
     * @return 0 for success, -1 for failure 
     */ 
    int set_temp_oversample(BMP388_TEMP_OVERSAMPLING oversample); 
    


    /**
     * reset the device 
     * @return 0 for success, -1 for error 
     */ 
    int reset(); 

    /**
     * check the device id 
     * currently looks for any non-zero and non-255 value 
     * @return 0 for valid chip id, -1 for error 
     */ 
    int check_id(); 

    /** 
     * write to the device 
     * @param reg register to write 
     * @param buffer buffer to write 
     * @param len length of the buffer 
     * @return 0 for success, -1 for error 
     */ 
    int write_reg(uint8_t reg, uint8_t *buffer, uint8_t len); 

    /** 
     * read from the devie 
     * @param reg resiter to read 
     * @param buffer buffer to read into 
     * @param len length of the buffer 
     * @return 0 for success, -1 for error
     */ 
    int read_reg(uint8_t reg, uint8_t *buffer, uint8_t len); 



}; 



#endif 