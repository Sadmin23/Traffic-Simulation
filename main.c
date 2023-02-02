#include "stm32f446xx.h"
#include "CLOCK.h"
#include "GPIO.h"
#include "SYS_INIT.h"
#include "USART.h"

int main (void)
{
	initClock();
	sysInit();
	
	GPIO_InitTypeDef x;
	
	GPIO_Init(GPIOA, &x);
	
	uint32_t start=getmsTick();
	
	while(1)
	{
		/*
		GPIO_WritePin(GPIOA, 0, GPIO_PIN_RESET);g1
		GPIO_WritePin(GPIOA, 1, GPIO_PIN_RESET);y1	
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_RESET);r1
		GPIO_WritePin(GPIOA, 8, GPIO_PIN_RESET);r2			
		GPIO_WritePin(GPIOA, 4, GPIO_PIN_RESET);y2
		GPIO_WritePin(GPIOA, 5, GPIO_PIN_RESET);g2	
		*/
		
		GPIO_WritePin(GPIOA, 0, GPIO_PIN_RESET);//start g1
		GPIO_WritePin(GPIOA, 8, GPIO_PIN_RESET);//start r2		
		ms_delay(3000);
		GPIO_WritePin(GPIOA, 0, GPIO_PIN_SET);//stop g1		
		GPIO_WritePin(GPIOA, 1, GPIO_PIN_RESET);//start y1
		ms_delay(2000);
		GPIO_WritePin(GPIOA, 1, GPIO_PIN_SET);//stop y1
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_RESET);//start r1		
		GPIO_WritePin(GPIOA, 8, GPIO_PIN_SET);//stop r2
		GPIO_WritePin(GPIOA, 5, GPIO_PIN_RESET);//start g2
		ms_delay(3000);
		GPIO_WritePin(GPIOA, 5, GPIO_PIN_SET);//stop g2		
		GPIO_WritePin(GPIOA, 4, GPIO_PIN_RESET);//start y2
		ms_delay(2000);
		GPIO_WritePin(GPIOA, 4, GPIO_PIN_SET);//stop y2
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_SET);//stop r2

	}	
	
}

