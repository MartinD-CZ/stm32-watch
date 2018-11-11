#include "stm32f0xx.h"
#include "interrupt.h"
#include "defines.h"

extern volatile uint8_t tSec, tMin, tHrs;
volatile uint8_t second_mark = 0;
volatile uint8_t hour_multiplex = 0;
volatile uint8_t minute_multiplex = 0;
volatile uint8_t i = 0;

extern volatile uint32_t draw[2];

void TIM16_IRQHandler()
{	
	//PB4_ON;
	
	//=======================
	//HOUR MULTIPLEX ROUTINE
	HOURS_LED_ALL_HIGH;
	hour_multiplex++;
	
	if (hour_multiplex == 1)
	{
		HOURS_B_LOW;
		HOURS_A_HIGH;
		
		if (((draw[0] >> 0) & 1) == 1)		HOURS_LED01_LOW;
		if (((draw[0] >> 10) & 1) == 1)		HOURS_LED23_LOW;
		if (((draw[0] >> 20) & 1) == 1)		HOURS_LED45_LOW;
		if (((draw[1] >> 0) & 1) == 1)		HOURS_LED67_LOW;
		if (((draw[1] >> 10) & 1) == 1)		HOURS_LED89_LOW;
		if (((draw[1] >> 20) & 1) == 1)		HOURS_LEDAB_LOW;
	}
	else if (hour_multiplex == 2) HOURS_A_LOW;
	else if (hour_multiplex == 3)
	{
		HOURS_A_LOW;
		HOURS_B_HIGH;

		if (((draw[0] >> 5) & 1) == 1)		HOURS_LED01_LOW;
		if (((draw[0] >> 15) & 1) == 1)		HOURS_LED23_LOW;
		if (((draw[0] >> 25) & 1) == 1)		HOURS_LED45_LOW;
		if (((draw[1] >> 5) & 1) == 1)		HOURS_LED67_LOW;
		if (((draw[1] >> 15) & 1) == 1)		HOURS_LED89_LOW;
		if (((draw[1] >> 25) & 1) == 1)		HOURS_LEDAB_LOW;
	}
	else if (hour_multiplex >= 4)
	{
		HOURS_B_LOW;
		hour_multiplex = 0;
	}
	
	//===================================
	//MINUTE MULTIPLEX ROUTINE
	minute_multiplex++;
	if (minute_multiplex > 7) minute_multiplex = 0;
	CPLX_ALL_INPUTS;
	
	switch (minute_multiplex)
	{
		case 0:
			CPLX0_OUTPUT_HIGH;
			if (((draw[0] >> 1) & 1) == 1)		CPLX1_OUTPUT_LOW;
			if (((draw[0] >> 2) & 1) == 1)		CPLX2_OUTPUT_LOW;
			if (((draw[0] >> 3) & 1) == 1)		CPLX3_OUTPUT_LOW;
			if (((draw[0] >> 4) & 1) == 1)		CPLX4_OUTPUT_LOW;
			if (((draw[0] >> 6) & 1) == 1)		CPLX5_OUTPUT_LOW;
			if (((draw[0] >> 7) & 1) == 1)		CPLX6_OUTPUT_LOW;
			break;
		case 1:
			CPLX1_OUTPUT_HIGH;
			if (((draw[0] >> 8) & 1) == 1)		CPLX0_OUTPUT_LOW;
			if (((draw[0] >> 9) & 1) == 1)		CPLX2_OUTPUT_LOW;
			if (((draw[0] >> 11) & 1) == 1)		CPLX3_OUTPUT_LOW;
			if (((draw[0] >> 12) & 1) == 1)		CPLX4_OUTPUT_LOW;
			if (((draw[0] >> 13) & 1) == 1)		CPLX5_OUTPUT_LOW;
			if (((draw[0] >> 14) & 1) == 1)		CPLX6_OUTPUT_LOW;
			break;
		case 2:
			CPLX2_OUTPUT_HIGH;
			if (((draw[0] >> 16) & 1) == 1)		CPLX0_OUTPUT_LOW;
			if (((draw[0] >> 17) & 1) == 1)		CPLX1_OUTPUT_LOW;
			if (((draw[0] >> 18) & 1) == 1)		CPLX3_OUTPUT_LOW;
			if (((draw[0] >> 19) & 1) == 1)		CPLX4_OUTPUT_LOW;
			if (((draw[0] >> 21) & 1) == 1)		CPLX5_OUTPUT_LOW;
			if (((draw[0] >> 22) & 1) == 1)		CPLX6_OUTPUT_LOW;
			break;
		case 3:
			CPLX3_OUTPUT_HIGH;
			if (((draw[0] >> 23) & 1) == 1)		CPLX0_OUTPUT_LOW;
			if (((draw[0] >> 24) & 1) == 1)		CPLX1_OUTPUT_LOW;
			if (((draw[0] >> 26) & 1) == 1)		CPLX2_OUTPUT_LOW;
			if (((draw[0] >> 27) & 1) == 1)		CPLX4_OUTPUT_LOW;
			if (((draw[0] >> 28) & 1) == 1)		CPLX5_OUTPUT_LOW;
			if (((draw[0] >> 29) & 1) == 1)		CPLX6_OUTPUT_LOW;
			break;
		case 4:
			CPLX4_OUTPUT_HIGH;
			if (((draw[1] >> 1) & 1) == 1)		CPLX0_OUTPUT_LOW;
			if (((draw[1] >> 2) & 1) == 1)		CPLX1_OUTPUT_LOW;
			if (((draw[1] >> 3) & 1) == 1)		CPLX2_OUTPUT_LOW;
			if (((draw[1] >> 4) & 1) == 1)		CPLX3_OUTPUT_LOW;
			if (((draw[1] >> 6) & 1) == 1)		CPLX5_OUTPUT_LOW;
			if (((draw[1] >> 7) & 1) == 1)		CPLX6_OUTPUT_LOW;
			break;
		case 5:
			CPLX5_OUTPUT_HIGH;
			if (((draw[1] >> 8) & 1) == 1)		CPLX0_OUTPUT_LOW;
			if (((draw[1] >> 9) & 1) == 1)		CPLX1_OUTPUT_LOW;
			if (((draw[1] >> 11) & 1) == 1)		CPLX2_OUTPUT_LOW;
			if (((draw[1] >> 12) & 1) == 1)		CPLX3_OUTPUT_LOW;
			if (((draw[1] >> 13) & 1) == 1)		CPLX4_OUTPUT_LOW;
			if (((draw[1] >> 14) & 1) == 1)		CPLX6_OUTPUT_LOW;
			break;
		case 6:
			CPLX6_OUTPUT_HIGH;
			if (((draw[1] >> 16) & 1) == 1)		CPLX0_OUTPUT_LOW;
			if (((draw[1] >> 17) & 1) == 1)		CPLX1_OUTPUT_LOW;
			if (((draw[1] >> 18) & 1) == 1)		CPLX2_OUTPUT_LOW;
			if (((draw[1] >> 19) & 1) == 1)		CPLX3_OUTPUT_LOW;
			if (((draw[1] >> 21) & 1) == 1)		CPLX4_OUTPUT_LOW;
			if (((draw[1] >> 22) & 1) == 1)		CPLX5_OUTPUT_LOW;
			break;
		case 7:
			CPLX7_OUTPUT_HIGH;
			if (((draw[1] >> 23) & 1) == 1)		CPLX0_OUTPUT_LOW;
			if (((draw[1] >> 24) & 1) == 1)		CPLX1_OUTPUT_LOW;
			if (((draw[1] >> 26) & 1) == 1)		CPLX2_OUTPUT_LOW;
			if (((draw[1] >> 27) & 1) == 1)		CPLX3_OUTPUT_LOW;
			if (((draw[1] >> 28) & 1) == 1)		CPLX4_OUTPUT_LOW;
			if (((draw[1] >> 29) & 1) == 1)		CPLX5_OUTPUT_LOW;
			break;
		default:
			break;
	}
		
	TIM16->SR &=~TIM_SR_CC1IF;
}

//1 second interrupt
void TIM14_IRQHandler()
{
	tSec++;
	if (tSec > 59)
	{
		tMin++;
		tSec = 0;
	}
	if (tMin > 59)
	{
		tHrs++;
		tMin = 0;
	}
	if (tHrs > 11)
	{
		tHrs = 0;
	}
	
	if (second_mark == 0)
	{
		//PB3_ON;
		second_mark = 1;
	}
	else
	{
		//PB3_OFF;
		second_mark = 0;
	}
	
	draw[0] = 0;
	draw[1] = 0;
	
	draw[tHrs < 6 ? 0 : 1] |= (1 << ((tHrs < 6 ? tHrs : tHrs - 6) * 5));
	draw[tMin < 30 ? 0 : 1] |= (1 << (tMin < 30 ? tMin : tMin - 30));
	draw[tSec < 30 ? 0 : 1] |= (1 << (tSec < 30 ? tSec : tSec - 30));

	TIM14->SR &=~TIM_SR_CC1IF;
}
