/*
 * STM32 watch
 *
 * Author : martin@embedblog.eu
 * Description: Firmware for an STM32F0 processor, used to drive the charlieplexed display - NOTE: I abandoned this project, so it is, by no means, finished or polished  
 * Link: http://embedblog.eu/?p=34
 */ 

#include "stm32f0xx.h"
#include "init.h"
#include "delay.h"
#include "interrupt.h"
#include "defines.h"

volatile uint8_t tSec = 0, tMin = 36, tHrs = 4;
volatile uint32_t draw[2];

int main(void)
{
	init_rcc();
	init_gpio();
	init_tim();

	
	while (1)
	{
		__wfi();

		/*for (uint8_t i = 0; i < 60; i ++)
		{
			draw[i < 30 ? 0 : 1] |= (1 << (i < 30 ? i : i - 30));
			_delay_ms(250);
			draw[0] = 0;
			draw[1] = 0;
			
			
		}*/
		
		//draw[0] = 0;
		//draw[1] = 0;
	}
}


