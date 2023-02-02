#include "stm32f446xx.h"
#include "CLOCK.h"
#include "GPIO.h"
#include "SYS_INIT.h"
#include "USART.h"

void GPIO_Config (void)
{
	
	// 1. Enable the GPIO CLOCK
	RCC->AHB1ENR |= (1<<0);  
	
	// 2. Set the Pin as OUTPUT
	GPIOA->MODER |= (1<<10);  // pin PA5(bits 11:10) as Output (01)
	
	// 3. Configure the OUTPUT MODE
	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;
}

void delay (uint32_t time)
{
	while (time--);
}

int main (void)
{
/*	
	initClock();
	GPIO_Config ();
	
	while (1)
	{
		GPIOA->BSRR |= (1<<5);  // Set the pin PA5
		delay (20000000); 
		GPIOA->BSRR |= ((1<<5) <<16);  // Reset pin PA5
		delay (20000000); 
	}
*/
	initClock();
	sysInit();
	
	GPIO_InitTypeDef x;
	
	GPIO_Init(GPIOA, &x);
	
	while(1)
	{
		GPIOA->BSRR |= (1<<7);
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_RESET);
		ms_delay(1000);
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_SET);
		ms_delay(1000);
	}	
	
}

