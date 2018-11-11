#ifndef INIT_H
#define INIT_H

void init_rcc(void)
{
	//divide clock by 8 to get 1 MHz system frequency
	RCC->CFGR |= RCC_CFGR_HPRE_DIV8;
	
	//enable GPIO
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOFEN;
}

void init_gpio(void)
{
	//PORTB2:7 as outputs
	GPIOB->MODER |= GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0  | GPIO_MODER_MODER7_0;

	//PORTA9:12; 15 as outputs
	GPIOA->MODER |= GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER15_0;
	
	GPIOA->OSPEEDR = 0xFFFFFFFF;
}

void init_tim(void)		
{
	//enable timer 17, used for delay
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
	
	//==========================================
	//enable timer 16, used for hour multiplex
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
	
	//set prescaler
	TIM16->PSC = 0;
	
	//update registers
	TIM16->EGR |= TIM_EGR_UG;
	
	//zero the counter
	TIM16->CNT = 0x00;
	
	//enable interrupt on CC1
	TIM16->DIER |= TIM_DIER_CC1IE;
	
	TIM16->ARR = 2500;
	
	NVIC_SetPriority(TIM16_IRQn, 3);
	NVIC_EnableIRQ(TIM16_IRQn);
	
	//enable timer
	TIM16->CR1 |= TIM_CR1_CEN;
	
	//=========================================
	//enable timer 14, used for second keeping
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	
	//set prescaler
	TIM14->PSC = 999;
	
	//update registers
	TIM14->EGR |= TIM_EGR_UG;
	
	//zero the counter
	TIM14->CNT = 0x00;
	
	//enable interrupt on CC1
	TIM14->DIER |= TIM_DIER_CC1IE;
	
	TIM14->ARR = 1000;
	
	NVIC_SetPriority(TIM14_IRQn, 1);
	NVIC_EnableIRQ(TIM14_IRQn);
	
	//enable timer
	TIM14->CR1 |= TIM_CR1_CEN;
}

#endif
