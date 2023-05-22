#include <BMP388.h> 

// #define BMP388_DEBUG 
// #define BMP388_DEBUG_CS PA9 // Used for external logic analyzer when making this 

int BMP388::begin(int cs_pin){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 begin() called"); 
    #endif
    /* initialize the device by the following steps: 
    initialize pins 
    initialize SPI settings 
    check deivce id 
    reset the device 
    write necessary settings for normal operation 
    read the calibration data set 
    set the device into normal mode
    */

    //initialize the pins 
    this->cs_pin = cs_pin; 
    pinMode(cs_pin,OUTPUT);
    digitalWrite(cs_pin, HIGH); 
    #ifdef BMP388_DEBUG_CS 
        pinMode(BMP388_DEBUG_CS,OUTPUT);
        digitalWrite(BMP388_DEBUG_CS, HIGH); 
    #endif 

    //initialize SPI settings 
    this->spi_settings = SPISettings(BMP388_SPI_SPEED, MSBFIRST, SPI_MODE0); 

    // check id 
    int status = check_id(); 
    if(status < 0){
        #ifdef BMP388_DEBUG
            Serial.println("BMP388 chip_id FAILED"); 
        #endif 
        return status; 
    }
    #ifdef BMP388_DEBUG
        Serial.println("BMP388 chip_id SUCCESS"); 
    #endif 

    // reset the device 
    status = reset(); 
    if(status < 0){
        #ifdef BMP388_DEBUG
            Serial.println("BMP388 reset FAILED"); 
        #endif 
        return status; 
    }
    #ifdef BMP388_DEBUG
        Serial.println("BMP388 reset SUCCESS"); 
    #endif 

    // write basic settings 
    // enable the pressure and temperature sensors 
    enable_sensors(); 
    // for now, set oversampling to 0
    set_pressure_oversample(BMP388_PRESSURE_OVERSAMPLE_X1); 
    set_temp_oversample(BMP388_TEMP_OVERSAMPLE_X1); 
    
    // read the calibration data 
    get_calibration_data(); 

    // set to normal mode 
    enable_normal_mode(); 

    return 0; 
}

int BMP388::get_new_data(BMP388_data *data){
    // check if a new update is available 
    int return_code = -1; 
    if(check_data_ready() == 0){
        // data is ready 
        read_all(); 
        //signify that new data was read 
        return_code = 0; 
    }
    else{
        return_code = 1; 
    }
    // copy over the data in the local struct 
    // perform a memcopy 
    memcpy(data, &cur_data, sizeof(cur_data)); 
    return return_code;
}

int BMP388::read_all(){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 read_all() called"); 
    #endif
    // read all the sensor data 
    uint8_t data_buffer[6] = {0}; 
    read_reg(BMP388_DATA_0_ADDR, data_buffer, 6); 
    uint32_t uncomp_pressure = (uint32_t)((uint32_t)(data_buffer[2] << 16) | (uint32_t)(data_buffer[1] << 8) | data_buffer[0]); 
    uint32_t uncomp_temp = (uint32_t)((uint32_t)(data_buffer[5] << 16) | (uint32_t)(data_buffer[4] << 8) | data_buffer[3]); 
    cur_data.temperature = compensate_temperature(uncomp_temp); 
    cur_data.pressure = compensate_pressure(uncomp_pressure, cur_data.temperature); 
    cur_data.timestamp = millis(); 
    return 0; 
}

int BMP388::check_errors(){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 check_errors() called"); 
    #endif
    // read the error register 
    uint8_t errors; 
    read_reg(BMP388_ERR_REG_ADDR, &errors, 1); 
    #ifdef BMP388_DEBUG
        if(errors != 0){
            Serial.print("\nBMP388 Errors! ");
            Serial.print(errors, BIN);  
            Serial.println(); 
        }
    #endif 
    return 0;
}



int BMP388::get_calibration_data(){
    // grab the calibration data from the device 
    uint8_t calibration_data_dump[BMP388_CALIBRATION_DATA_LENGTH]; 
    int status = read_reg(BMP388_CALIBRATION_DATA_START_ADDR, calibration_data_dump, BMP388_CALIBRATION_DATA_LENGTH); 
    if(status < 0){
        return status; 
    }
    /*
    Serial.println("Calibration data: "); 
    for(int i = 0; i < BMP388_CALIBRATION_DATA_LENGTH; i ++){
        Serial.println(calibration_data_dump[i], BIN); 
    }
    Serial.println();
    */ 
    // start parsing the data 
    // convert to the correct types 
    double t1 = (uint16_t)(calibration_data_dump[1] << 8) | calibration_data_dump[0]; 
    double t2 = (uint16_t)(calibration_data_dump[3] << 8) | calibration_data_dump[2]; 
    double t3 = (int8_t)calibration_data_dump[4]; 
    double p1 = (int16_t)(calibration_data_dump[6] << 8) | calibration_data_dump[5];  
    double p2 = (int16_t)(calibration_data_dump[8] << 8) | calibration_data_dump[7];
    double p3 = (int8_t)(calibration_data_dump[9]);
    double p4 = (int8_t)(calibration_data_dump[10]);
    double p5 = (uint16_t)(calibration_data_dump[12] << 8) | calibration_data_dump[11];
    double p6 = (uint16_t)(calibration_data_dump[14] << 8) | calibration_data_dump[13];
    double p7 = (int8_t)(calibration_data_dump[15]);
    double p8 = (int8_t)(calibration_data_dump[16]);
    double p9 = (int16_t)(calibration_data_dump[18] << 8) | calibration_data_dump[17];
    double p10 = (int8_t)(calibration_data_dump[19]);
    double p11 = (int8_t)(calibration_data_dump[20]);
    /* 
    Serial.println("t1: " + String(t1)); 
    Serial.println("t2: " + String(t2)); 
    Serial.println("t3: " + String(t3)); 
    */ 
    calib_data.par_t1 = t1 * 256.0f; 
    calib_data.par_t2 = t2 / 1073741824.0f; 
    calib_data.par_t3 = t3 / 281474976710656.0f; 
    calib_data.par_p1 = (p1 - 16384) / 1048576.0f; 
    calib_data.par_p2 = (p2 - 16384) / 536870912.0f; 
    calib_data.par_p3 = p3 / 4294967296.0f; 
    calib_data.par_p4 = p4 / 137438953472.0f; 
    calib_data.par_p5 = p5 * 8.0f; 
    calib_data.par_p6 = p6 / 64.0f; 
    calib_data.par_p7 = p7 / 256.0f; 
    calib_data.par_p8 = p8 / 32768.0f; 
    calib_data.par_p9 = p9 / 281474976710656.0f; 
    calib_data.par_p10 = p10 / 281474976710656.0f; 
    calib_data.par_p11 = p11 / 36893488147419103232.0f;  
    /*
    Serial.println(String(calib_data.par_t1,10)); 
    Serial.println(String(calib_data.par_t2,10)); 
    Serial.println(String(calib_data.par_t3,10)); 
    Serial.println("1 " + String(calib_data.par_p1,10)); 
    Serial.println(String(calib_data.par_p2,10)); 
    Serial.println(String(calib_data.par_p3,10));
    Serial.println(String(calib_data.par_p4,10)); 
    Serial.println(String(calib_data.par_p5,10)); 
    Serial.println(String(calib_data.par_p6,10));
    Serial.println("7 " + String(calib_data.par_p7,10)); 
    Serial.println(String(calib_data.par_p8,10)); 
    Serial.println(String(calib_data.par_p9,10));
    Serial.println(String(calib_data.par_p10,10)); 
    Serial.println(String(calib_data.par_p11,10)); 
    */
    return 0; 
}

float BMP388::compensate_temperature(uint32_t uncomp_temp){
	double partial_data1;
	double partial_data2;

	partial_data1 = (double)(uncomp_temp - calib_data.par_t1);
	partial_data2 = (double)(partial_data1 * calib_data.par_t2);
	/* Update the compensated temperature in calib structure since this is
	   needed for pressure calculation */
	return partial_data2 + (partial_data1 * partial_data1) * calib_data.par_t3;
}

float BMP388:: compensate_pressure(uint32_t uncomp_pressure, float comp_temperature){
    //double comp_press;
    double partial_data1; 
    double partial_data2; 
    double partial_data3; 
    double partial_data4; 
    double partial_out1; 
    double partial_out2; 

    partial_data1 = calib_data.par_p6 * comp_temperature; 
    partial_data2 = calib_data.par_p7 * (comp_temperature * comp_temperature);
    partial_data3 = calib_data.par_p8 * (comp_temperature * comp_temperature * comp_temperature);
    partial_out1 = calib_data.par_p5 + partial_data1 + partial_data2 + partial_data3;

    partial_data1 = calib_data.par_p2 * comp_temperature;
    partial_data2 = calib_data.par_p3 * (comp_temperature * comp_temperature);
    partial_data3 = calib_data.par_p4 * (comp_temperature * comp_temperature * comp_temperature);
    partial_out2 = (double)uncomp_pressure * (calib_data.par_p1 + partial_data1 + partial_data2 + partial_data3);
    partial_data1 = (double)uncomp_pressure * (double)uncomp_pressure; 
    partial_data2 = calib_data.par_p9 + calib_data.par_p10 * comp_temperature;
    partial_data3 = partial_data1 * partial_data2;
    partial_data4 = partial_data3 + ((double)uncomp_pressure * (double)uncomp_pressure * (double)uncomp_pressure) * calib_data.par_p11;
    return (float)(partial_out1 + partial_out2 + partial_data4);
}

int BMP388::check_data_ready(){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 check_data_ready() called"); 
    #endif
    // read the PWR_CTRL register 
    uint8_t status; 
    read_reg(BMP388_STATUS_ADDR, &status, 1); 
    // check for pressure and data ready 
    // Serial.print("STATUS REG: "); Serial.print(status, HEX); Serial.println(); 
    if(status & 0b01100000) return 0; 
    return -1; 
}

int BMP388::enable_normal_mode(){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 enable_normal_mode() called"); 
    #endif
    // read the PWR_CTRL register 
    uint8_t pwr_crtl; 
    read_reg(BMP388_PWR_CTRL_ADDR, &pwr_crtl, 1); 
    // scrub it 
    pwr_crtl &= 0b11001111; 
    pwr_crtl |= 0x03 << 4; 
    return write_reg(BMP388_PWR_CTRL_ADDR, &pwr_crtl, 1); 
}

int BMP388::enable_sensors(){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 enable_sensors() called"); 
    #endif
    // read the PWR_CTRL register 
    uint8_t pwr_crtl; 
    read_reg(BMP388_PWR_CTRL_ADDR, &pwr_crtl, 1); 
    // scrub it 
    pwr_crtl &= 0b11111100; 
    pwr_crtl |= 0x03; 
    return write_reg(BMP388_PWR_CTRL_ADDR, &pwr_crtl, 1); 
}

int BMP388::set_pressure_oversample(BMP388_PRESSURE_OVERSAMPLING oversample){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 set_pressure_oversample() called"); 
    #endif 
    // read the OSR register 
    uint8_t osr_reg; 
    read_reg(BMP388_OSR_ADDR, &osr_reg, 1); 
    // Serial.print("Orig OSR value: "); Serial.print(osr_reg, HEX); Serial.println(); 
    // scrub it 
    osr_reg &= 0b11111000;
    osr_reg |= oversample; 
    // Serial.print("New OSR value: "); Serial.print(osr_reg, HEX); Serial.println(); 
    // write it 
    return write_reg(BMP388_OSR_ADDR, &osr_reg, 1);  
}

int BMP388::set_temp_oversample(BMP388_TEMP_OVERSAMPLING oversample){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 set_temp_oversample() called"); 
    #endif 
    // read the OSR register 
    uint8_t osr_reg; 
    read_reg(BMP388_OSR_ADDR, &osr_reg, 1); 
    // Serial.print("Orig OSR value: "); Serial.print(osr_reg, HEX); Serial.println(); 
    // scrub it 
    osr_reg &= 0b11000111;
    osr_reg |= oversample << 3; 
    // Serial.print("New OSR value: "); Serial.print(osr_reg, HEX); Serial.println(); 
    // write it 
    return write_reg(BMP388_OSR_ADDR, &osr_reg, 1);  
}

int BMP388::reset(){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 reset() called"); 
    #endif 
    // write to the CMD register 
    uint8_t reset_command = 0xB6; 
    write_reg(BMP388_CMD_ADDR, &reset_command, 1); 
    // there is no documentation of the reset delay, assume 5 ms 
    delay(5); 
    return 0; 
}


int BMP388::check_id(){
    #ifdef BMP388_DEBUG 
        Serial.println("BMP388 check_id() called"); 
    #endif 
    // grab the id 
    uint8_t chip_id; 
    int status = read_reg(BMP388_CHIP_ID_ADDR, &chip_id, 1); 
    if(status < 0) return status; 
    if(chip_id != 0 && chip_id != 255){
        // presumably valid 
        return 0; 
    }
    return -1; 
}


int BMP388::read_reg(uint8_t reg, uint8_t *buffer, uint8_t len){
    #ifdef BMP388_DEBUG 
        Serial.print("\n\tBMP388 SPI$"); Serial.print(reg, HEX); Serial.print("<=="); 
    #endif 
    // convert the reg to a legit read value 
    reg = reg | 0x80; 
    SPI.beginTransaction(spi_settings); 
    // chip select 
    digitalWrite(10, LOW); 
    #ifdef BMP388_DEBUG_CS
        digitalWrite(BMP388_DEBUG_CS,LOW); 
    #endif 
    //digitalWrite(PA9, LOW); 
    // transfer the reg 
    SPI.transfer(reg); 
    // read a dummy value 
    SPI.transfer(0x00); 
    // read the buffer 
    while(len --){
        *buffer = SPI.transfer(0x00); 
        #ifdef BMP388_DEBUG
            Serial.print(*buffer,HEX); Serial.print(","); 
        #endif 
        buffer ++; 
    }
    // close out the transaction 
    digitalWrite(10, HIGH); 
    #ifdef BMP388_DEBUG_CS
        digitalWrite(BMP388_DEBUG_CS,HIGH); 
    #endif 
    SPI.endTransaction(); 
    #ifdef BMP388_DEBUG
        Serial.print("\n"); 
    #endif 
    return 0; 
}



int BMP388::write_reg(uint8_t reg, uint8_t *buffer, uint8_t len){
    #ifdef BMP388_DEBUG 
        Serial.print("\n\tBMP388 SPI$"); Serial.print(reg, HEX); Serial.print("==>"); 
    #endif 
    SPI.beginTransaction(spi_settings); 
    // chip select 
    digitalWrite(10, LOW); 
    #ifdef BMP388_DEBUG_CS
        digitalWrite(BMP388_DEBUG_CS,LOW); 
    #endif 
    // transfer the reg 
    SPI.transfer(reg); 
    // read the buffer 
    while(len --){
        SPI.transfer(*buffer); 
    #ifdef BMP388_DEBUG
        Serial.print(*buffer,HEX); Serial.print(","); 
    #endif 
        buffer ++; 
    }
    // close out the transaction 
    digitalWrite(10, HIGH); 
    #ifdef BMP388_DEBUG_CS
        digitalWrite(BMP388_DEBUG_CS,HIGH); 
    #endif 
    SPI.endTransaction(); 
    #ifdef BMP388_DEBUG
        Serial.print("\n"); 
    #endif 
    return 0; 
}