#include "stm32f446xx.h"
#include "CLOCK.h"
#include "GPIO.h"
#include "SYS_INIT.h"
#include "USART.h"

typedef struct
{
    uint32_t green;
    uint32_t yellow;
    uint32_t red;
} traffic;
typedef struct
{
    traffic mode;
    uint32_t top;
    uint32_t bottom;
    uint32_t light;
} lane;

traffic normal = {15000, 5000, 20000};
traffic delayed = {25000, 5000, 30000};

int val[3]={6,9,10};

uint32_t trafficGenerator(void)
{
    return rand() % 3 + 1;
}
int main (void)
{
	
	
	initClock();
	sysInit();
	
	GPIO_InitTypeDef x;
	
	GPIO_Init(GPIOA, &x);
	GPIO_Init(GPIOB, &x);
	
	while(1)
	{
/*
		GPIO_WritePin(GPIOA, 0, GPIO_PIN_RESET);//g1
		GPIO_WritePin(GPIOA, 1, GPIO_PIN_RESET);//y1	
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_RESET);//r1
		GPIO_WritePin(GPIOA, 8, GPIO_PIN_RESET);//r2			
		GPIO_WritePin(GPIOA, 4, GPIO_PIN_RESET);//y2
		GPIO_WritePin(GPIOA, 5, GPIO_PIN_RESET);//g2		
*/	
/*
		GPIO_WritePin(GPIOA, 6, GPIO_PIN_RESET);//g1
		GPIO_WritePin(GPIOA, 9, GPIO_PIN_RESET);//y1	
		GPIO_WritePin(GPIOA, 10, GPIO_PIN_RESET);//r1
		GPIO_WritePin(GPIOA, 11, GPIO_PIN_RESET);//r2			
		GPIO_WritePin(GPIOB, 5, GPIO_PIN_RESET);//g2	
		GPIO_WritePin(GPIOB, 10, GPIO_PIN_RESET);//g2	
*/		
		
		int i;
		
		GPIO_WritePin(GPIOA, 0, GPIO_PIN_RESET);//start g1
		GPIO_WritePin(GPIOA, 8, GPIO_PIN_RESET);//start r2		
//		ms_delay(3000);
		
		for (i=0; i<3000/600; i++)
		{
			GPIO_WritePin(GPIOA, 10, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOA, 10, GPIO_PIN_SET);			
			GPIO_WritePin(GPIOA, 9, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOA, 9, GPIO_PIN_SET);
			GPIO_WritePin(GPIOA, 6, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOA, 6, GPIO_PIN_SET);
		}
		
		GPIO_WritePin(GPIOA, 0, GPIO_PIN_SET);//stop g1		
		GPIO_WritePin(GPIOA, 1, GPIO_PIN_RESET);//start y1
//		ms_delay(2000);

		for (i=0; i<3000/600; i++)
		{
			GPIO_WritePin(GPIOA, 10, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOA, 10, GPIO_PIN_SET);			
			GPIO_WritePin(GPIOA, 9, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOA, 9, GPIO_PIN_SET);
			GPIO_WritePin(GPIOA, 6, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOA, 6, GPIO_PIN_SET);
		}

		GPIO_WritePin(GPIOA, 1, GPIO_PIN_SET);//stop y1
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_RESET);//start r1		
		GPIO_WritePin(GPIOA, 8, GPIO_PIN_SET);//stop r2
		GPIO_WritePin(GPIOA, 5, GPIO_PIN_RESET);//start g2
//		ms_delay(3000);

		for (i=0; i<3000/600; i++)
		{
			GPIO_WritePin(GPIOB, 10, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOB, 10, GPIO_PIN_SET);			
			GPIO_WritePin(GPIOB, 5, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOB, 5, GPIO_PIN_SET);
			GPIO_WritePin(GPIOA, 11, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOA, 11, GPIO_PIN_SET);
		}

		GPIO_WritePin(GPIOA, 5, GPIO_PIN_SET);//stop g2		
		GPIO_WritePin(GPIOA, 4, GPIO_PIN_RESET);//start y2
//		ms_delay(2000);

		for (i=0; i<3000/600; i++)
		{
			GPIO_WritePin(GPIOB, 10, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOB, 10, GPIO_PIN_SET);			
			GPIO_WritePin(GPIOB, 5, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOB, 5, GPIO_PIN_SET);
			GPIO_WritePin(GPIOA, 11, GPIO_PIN_RESET);
			ms_delay(200);
			GPIO_WritePin(GPIOA, 11, GPIO_PIN_SET);
		}

		GPIO_WritePin(GPIOA, 4, GPIO_PIN_SET);//stop y2
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_SET);//stop r2

	}	
	
}

