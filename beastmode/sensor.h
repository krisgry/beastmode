/*
 * sensor.h
 *
 * Created: 16.09.2013 18:20:22
 *  Author: Jesper
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_


#define ACCADDR 0x38
#define ACCXLSB_REG 0x02 //bit 7 and 6
#define ACCXMSB_REG 0x03
#define ACCYLSB_REG 0x04 //bit 7 and 6
#define ACCYMSB_REG 0x05
#define ACCZLSB_REG 0x06 //bit 7 and 6
#define ACCZMSB_REG 0x07
#define ACCTEMP_REG 0x08

#define ACC_CTRL3_REG 0x15

#define ACC_CALIB_X_REG 0x16 //
#define ACC_CALIB_Y_REG 0x17
#define ACC_CALIB_Z_REG 0x18
#define ACC_CALIB_TEMP_REG 0x19

#define ACC_NEW_DATA_INT_PIN AVR32_PIN_PC3
#define ACC_NEW_DATA_INT_ENABLE_BIT 5 //in ACC_CTRL3_REG
#define ACC_RESET_INT_BIT 6 //in CTRL0_REG

#define ACC_LSB_SENS_2G 256 //lsb per g
#define ACC_LSB_SENS_4G 128 //lsb per g
#define ACC_LSB_SENS_8G 64 //lsb per g
#define ACC_SENS ACC_LSB_SENS_4G


typedef struct
{
	double x;
	double y;
	double z;
}axis3_t;

axis3_t acc_reading; //updated by interrupt sensor_acc_new_data

status_code_t sensor_acc_write(uint8_t reg_addr,uint8_t data);

status_code_t sensor_acc_read(uint8_t reg_addr, uint8_t *result);

void sensor_acc_init();

/*Read from acc on interrupt that new data is ready*/
void sensor_acc_new_data_int_handle(void);


#endif /* SENSOR_H_ */