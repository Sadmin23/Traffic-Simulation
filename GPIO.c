#include "GPIO.h"
#include "CLOCK.h"

void GPIO_WritePin(GPIO_TypeDef *GPIOx,uint16_t GPIO_pin,GPIO_PinState PinState)
{
		if (PinState==0)
			GPIOx->BSRR |= (1<<GPIO_pin);
		else
			GPIOx->BSRR |= ((1<<GPIO_pin)<<16);
}
void GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_InitTypeDef *GPIO_Init)
{
// You need to implement this function	

		RCC->AHB1ENR |= (1<<0);
	
		GPIOx->MODER |= (1<<14);
		
		GPIOx->OTYPER = 0;
		GPIOx->OSPEEDR = 0;
}
