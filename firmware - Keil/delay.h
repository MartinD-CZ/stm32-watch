#ifndef DELAY_H
#define DELAY_H

//delays the program execution by given amount of microseconds; max value = 65535 uS = 65 mS; min value = 2;
void _delay_us(uint16_t us)
{
	//us--;
	
	//set prescaler (47 + 1 = 48)
	TIM17->PSC = 0;
	
	//update registers
	TIM17->EGR = TIM_EGR_UG;
	
	//zero the counter
	TIM17->CNT = 0;
	
	//enable timer
	TIM17->CR1 |= TIM_CR1_CEN;
	
	while (us > TIM17->CNT);

	//disable timer
	TIM17->CR1 &=~ TIM_CR1_CEN;
}

//delays the program execution by given amount of miliseconds; max value = 65535 mS = 65 S; min value = 2;
void _delay_ms(uint16_t ms)
{
	//set prescaler (47 + 1 = 48)
	TIM17->PSC = 999;
	
	//update registers
	TIM17->EGR = TIM_EGR_UG;
	
	//zero the counter
	TIM17->CNT = 0;
	
	//enable timer
	TIM17->CR1 |= TIM_CR1_CEN;
	
	while (ms > TIM17->CNT);

	//disable timer
	TIM17->CR1 &=~ TIM_CR1_CEN;
}
#endif
