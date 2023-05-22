#ifndef _BMP388_DEFS_H_
#define _BMP388_DEFS_H_


//SPI Settings 
#define BMP388_SPI_SPEED                    10000000 // 10 MHz 


// Register Address 
#define BMP388_CHIP_ID_ADDR                 (0x00)
#define BMP388_ERR_REG_ADDR                 (0x02)
#define BMP388_STATUS_ADDR                  (0x03)
#define BMP388_DATA_0_ADDR                  (0x04)
#define BMP388_DATA_1_ADDR                  (0x05)          
#define BMP388_DATA_2_ADDR                  (0x06)
#define BMP388_DATA_3_ADDR                  (0x07)
#define BMP388_DATA_4_ADDR                  (0x08)
#define BMP388_DATA_5_ADDR                  (0x09)
#define BMP388_SENSOR_TIME_0_ADDR           (0x0C)
#define BMP388_SENSOR_TIME_1_ADDR           (0x0D)
#define BMP388_SENSOR_TIME_2_ADDR           (0x0E)
#define BMP388_EVENT_ADDR                   (0x10)
#define BMP388_INT_STATUS_ADDR              (0x11)
#define BMP388_FIFO_LENGTH_0_ADDR           (0x12)
#define BMP388_FIFO_LENGTH_1_ADDR           (0x13)
#define BMP388_FIFO_DATA_ADDR               (0x14)
#define BMP388_FIFO_WTM_0_ADDR              (0x15)
#define BMP388_FIFO_WTM_1_ADDR              (0x16)
#define BMP388_FIFO_CONFIG_1_ADDR           (0x17)
#define BMP388_FIFO_CONFIG_2_ADDR           (0x18)
#define BMP388_INT_CTRL_ADDR                (0x19)
#define BMP388_IF_CONF_ADDR                 (0x1A)
#define BMP388_PWR_CTRL_ADDR                (0x1B)
#define BMP388_OSR_ADDR                     (0x1C)
#define BMP388_ODR_ADDR                     (0x1D)
#define BMP388_CONFIG_ADDR                  (0x1F)
#define BMP388_CMD_ADDR                     (0x7E) 

// calibration data 
#define BMP388_CALIBRATION_DATA_START_ADDR  (0x31)
#define BMP388_CALIBRATION_DATA_LENGTH      (21)

//Chip errors 
#define BMP388_FATAL_ERR_SEL                (1 << 0)
#define BMP388_CMD_ERR_SEL                  (1 << 1)


// settings 
#define BMP388_PRESS_EN_SEL                 (1 << 0)
#define BMP388_TEMP_EN_SEL                  (1 << 1)


#endif 