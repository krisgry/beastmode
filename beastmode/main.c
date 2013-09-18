/*
 * beastmode.c
 *
 * Created: 16.09.2013 18:15:31
 *  Author: Jesper
 */ 


#include <avr32/io.h>
#include "sensor.h"



int main(void)
{
	sensor_acc_init();
	while(1);
// 	avr32_gpio_port_t *led_port = &AVR32_GPIO.port[MYLED/32]; //.pvr
// 
// 	avr32_gpio_port_t *button_port = &AVR32_GPIO.port[GPIO_PUSH_BUTTON_0/32]; //.pvr
// 	button_port->gpers = (1<<(GPIO_PUSH_BUTTON_0&0x1f));
// 	button_port->oderc = (1<<(GPIO_PUSH_BUTTON_0&0x1f));
// 	
//     while(1)
//     {
// 		while ((button_port->pvr& (1<<(GPIO_PUSH_BUTTON_0&0x1f))))
// 			;
// 		led_port->gpers = (1<<(MYLED&0x1f));
// 		led_port->oders = (1<<(MYLED&0x1f));
// 		led_port->ovrt = (1<<(MYLED&0x1f));
// 		
//         //TODO:: Please write your application code 
//     }
}