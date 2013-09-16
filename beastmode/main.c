/*
 * beastmode.c
 *
 * Created: 16.09.2013 18:15:31
 *  Author: Jesper
 */ 


#include <avr32/io.h>


#define LED0_GPIO                   (AVR32_PIN_PB03)
#define LED1_GPIO                   (AVR32_PIN_PX22)
#define LED2_GPIO                   (AVR32_PIN_PB02)
#define LED3_GPIO                   (AVR32_PIN_PB06)
#define GPIO_PUSH_BUTTON_0          (AVR32_PIN_PB01)
#define MYLED LED1_GPIO

int main(void)
{
	avr32_gpio_port_t *led_port = &AVR32_GPIO.port[MYLED/32]; //.pvr

	avr32_gpio_port_t *button_port = &AVR32_GPIO.port[GPIO_PUSH_BUTTON_0/32]; //.pvr
	button_port->gpers = (1<<(GPIO_PUSH_BUTTON_0&0x1f));
	button_port->oderc = (1<<(GPIO_PUSH_BUTTON_0&0x1f));
	
    while(1)
    {
		while ((button_port->pvr& (1<<(GPIO_PUSH_BUTTON_0&0x1f))))
			;
		led_port->gpers = (1<<(MYLED&0x1f));
		led_port->oders = (1<<(MYLED&0x1f));
		led_port->ovrt = (1<<(MYLED&0x1f));
		
        //TODO:: Please write your application code 
    }
}