/*
 * sensor.c
 *
 * Created: 16.09.2013 18:20:13
 *  Author: Jesper
 */
#include <asf.h>
#include "sensor.h"
#include <avr32/io.h>

#define LED0_GPIO                   (AVR32_PIN_PB03)
#define LED1_GPIO                   (AVR32_PIN_PX22)
#define LED2_GPIO                   (AVR32_PIN_PB02)
#define LED3_GPIO                   (AVR32_PIN_PB06)
#define GPIO_PUSH_BUTTON_0          (AVR32_PIN_PB01)
#define MYLED LED3_GPIO
status_code_t sensor_acc_write(uint8_t reg_addr,uint8_t data){
	uint8_t buf[] = {reg_addr,data};
	return twim_write(&AVR32_TWIM0, buf, 2, ACCADDR, 0);
}

status_code_t sensor_acc_read(uint8_t reg_addr, uint8_t *result){
	twim_write(&AVR32_TWIM0, &reg_addr, 1, ACCADDR, 0);
	#warning "verify reg_addr";
	return twim_read (&AVR32_TWIM0, result, 6, ACCADDR, 0);
}
		avr32_gpio_port_t *led_port = &AVR32_GPIO.port[MYLED/32];
void sensor_acc_init(){

		led_port->gpers = (1<<(MYLED&0x1f));
		led_port->oders = (1<<(MYLED&0x1f));
	uint8_t initial_data[6];
	sensor_acc_read(ACC_CTRL3_REG, initial_data);
	sensor_acc_write(ACC_CTRL3_REG, initial_data[0]|(1<<ACC_NEW_DATA_INT_ENABLE_BIT));
	
	Disable_global_interrupt();
	INTC_init_interrupts(); //TODO: should it be here??
	INTC_register_interrupt(&sensor_acc_new_data_int_handle, AVR32_GPIO_IRQ_0 + ACC_NEW_DATA_INT_PIN/8,	AVR32_INTC_INT0);

	// Enable all interrupts.
	Enable_global_interrupt();
}
uint32_t n = 0; 
/*Read from acc on interrupt that new data is ready*/
__attribute__((__interrupt__))
void sensor_acc_new_data_int_handle(void){
	uint8_t data[6];
	sensor_acc_read(ACCXLSB_REG,data);//read registers for x, y and z
	//reading automatically resets interrupt
	acc_reading.x = ((data[0]>>6) | (data[1]<<2))/ACC_SENS;
	acc_reading.y = ((data[2]>>6) | (data[3]<<2))/ACC_SENS;
	acc_reading.z = ((data[4]>>6) | (data[5]<<2))/ACC_SENS;
	if(!(n%10000)){
		n = 0;
		led_port->ovrt = (1<<(MYLED&0x1f));
	}
	n++;
}