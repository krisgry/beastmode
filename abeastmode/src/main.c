/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "sensor.h"

#define MYLED AVR32_PIN_PB02
#define PBA_HZ 115000

int main (void)
{
	board_init();

	twim_options_t twim_opt;
	twim_opt.chip = 0x38;
	twim_opt.pba_hz = PBA_HZ;
	twim_opt.speed = TWI_STD_MODE_SPEED;
	twim_opt.smbus = 0;
	
	twim_master_init(&AVR32_TWIM0, &twim_opt);
	sensor_acc_init();
	avr32_gpio_port_t *led_port = &AVR32_GPIO.port[MYLED/32]; //.pvr
	
	// 	avr32_gpio_port_t *button_port = &AVR32_GPIO.port[GPIO_PUSH_BUTTON_0/32]; //.pvr
	// 	button_port->gpers = (1<<(GPIO_PUSH_BUTTON_0&0x1f));
	// 	button_port->oderc = (1<<(GPIO_PUSH_BUTTON_0&0x1f));
	//
	uint32_t i = 0;
	while(1)
	{
		// 		while ((button_port->pvr& (1<<(GPIO_PUSH_BUTTON_0&0x1f))))
		// 			;
		if((i==1000)){
			led_port->gpers = (1<<(MYLED&0x1f));
			led_port->oders = (1<<(MYLED&0x1f));
			led_port->ovrt = (1<<(MYLED&0x1f));
			//
			i = 0;
		}
		i++;
	}
	// Insert application code here, after the board has been initialized.
}
