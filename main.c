#include "stm32f446xx.h"
#include "CLOCK.h"
#include "GPIO.h"
#include "SYS_INIT.h"
#include "USART.h"
#include "time.h"

enum
{
    A,
    B,
    C
};

typedef struct
{
    int green;
    int yellow;
    int red;
} traffic;

traffic normal = {18000, 6000, 24000};
traffic delayed = {24000, 6000, 30000};

typedef struct
{
    int Port;
    uint16_t Pin;
} PortPin;

PortPin white2[2][3] = {{{A, 12}, {A, 11}, {B, 0}}, {{A, 8}, {A, 9}, {A, 10}}};
PortPin white[2][3] = {{{B, 1}, {B, 2}, {B, 5}}, {{B, 8}, {B, 7}, {B, 6}}};

typedef struct
{
    PortPin Green;
    PortPin Yellow;
    PortPin Red;
		PortPin White[2][3];
		
} lane;

//lane vertical

	
GPIO_TypeDef * Find_Port(int Port_no)
{
    if (Port_no == A)
				return GPIOA;
    else if (Port_no == B)
				return GPIOB;
    else if (Port_no == C)
				return GPIOC;
}	
	
int trafficGenerator(void)
{
    return rand() % 2 + 1;
}
int main (void)
{	
//    srand(time(0));
	
	traffic mode = normal;
	
	initClock();
	sysInit();
	
	GPIO_InitTypeDef z;
	
	GPIO_Init(GPIOA, &z);
	GPIO_Init(GPIOB, &z);
	
	while(1)
	{

		int i, j, k, x;
		
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_RESET);//start g1
		GPIO_WritePin(GPIOA, 0, GPIO_PIN_RESET);//start r2		
//		ms_delay(3000);
		
		for (i=0; i<mode.green/6000; i++)
		{
			x = trafficGenerator();
			
			for (j=0; j<x; j++)
			{
				int a = white2[0][j].Port;
				uint16_t b = white2[0][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
			}
			
			int y = trafficGenerator();
			
			for (j=0; j<y; j++)
			{
				int a = white2[1][j].Port;
				uint16_t b = white2[1][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
			}			
			
			for (j=0; j<6000/600; j++)
			{
				for (k=0; k<3; k++)
				{
					int a = white[0][k].Port;
					uint16_t b = white[0][k].Pin;
					int c = white[1][k].Port;
					uint16_t d = white[1][k].Pin;
					GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
					GPIO_WritePin(Find_Port(c),d, GPIO_PIN_RESET);					
					ms_delay(200);
					GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
					GPIO_WritePin(Find_Port(c),d, GPIO_PIN_SET);
				}
			}
			for (j=0; j<x; j++)
			{
				int a = white[0][j].Port;
				uint16_t b = white[0][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
			}
			for (j=0; j<y; j++)
			{
				int a = white[1][j].Port;
				uint16_t b = white[1][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
			}	
		}
		
		GPIO_WritePin(GPIOA, 7, GPIO_PIN_SET);//stop g1		
		GPIO_WritePin(GPIOA, 6, GPIO_PIN_RESET);//start y1
//		ms_delay(2000);

		for (i=0; i<mode.yellow/6000; i++)
		{
			x = trafficGenerator();
			
			for (j=0; j<x; j++)
			{
				int a = white2[0][j].Port;
				uint16_t b = white2[0][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
			}
			
			int y = trafficGenerator();
			
			for (j=0; j<y; j++)
			{
				int a = white2[1][j].Port;
				uint16_t b = white2[1][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
			}			
			
			for (j=0; j<6000/600; j++)
			{
				for (k=0; k<3; k++)
				{
					int a = white[0][k].Port;
					uint16_t b = white[0][k].Pin;
					int c = white[1][k].Port;
					uint16_t d = white[1][k].Pin;
					GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
					GPIO_WritePin(Find_Port(c),d, GPIO_PIN_RESET);					
					ms_delay(200);
					GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
					GPIO_WritePin(Find_Port(c),d, GPIO_PIN_SET);
				}
			}
			for (j=0; j<x; j++)
			{
				int a = white2[0][j].Port;
				uint16_t b = white2[0][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
			}
			for (j=0; j<y; j++)
			{
				int a = white2[1][j].Port;
				uint16_t b = white2[1][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
			}
			if (x<3 && y<3)
				mode = delayed;
			else 
				mode = normal;
		}
		
		GPIO_WritePin(GPIOA, 6, GPIO_PIN_SET);//stop y1
		GPIO_WritePin(GPIOA, 5, GPIO_PIN_RESET);//start r1		
		GPIO_WritePin(GPIOA, 0, GPIO_PIN_SET);//stop r2
		GPIO_WritePin(GPIOA, 4, GPIO_PIN_RESET);//start g2
//		ms_delay(3000);

		for (i=0; i<mode.green/6000; i++)
		{
			x = trafficGenerator();
			
			for (j=0; j<x; j++)
			{
				int a = white[0][j].Port;
				uint16_t b = white[0][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
			}
			
			int y = trafficGenerator();
			
			for (j=0; j<y; j++)
			{
				int a = white[1][j].Port;
				uint16_t b = white[1][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
			}			
			
			for (j=0; j<6000/600; j++)
			{
				for (k=0; k<3; k++)
				{
					int a = white2[0][k].Port;
					uint16_t b = white2[0][k].Pin;
					int c = white2[1][k].Port;
					uint16_t d = white2[1][k].Pin;
					GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
					GPIO_WritePin(Find_Port(c),d, GPIO_PIN_RESET);					
					ms_delay(200);
					GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
					GPIO_WritePin(Find_Port(c),d, GPIO_PIN_SET);
				}
			}
			for (j=0; j<x; j++)
			{
				int a = white[0][j].Port;
				uint16_t b = white[0][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
			}
			for (j=0; j<y; j++)
			{
				int a = white[1][j].Port;
				uint16_t b = white[1][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
			}	
		}

		GPIO_WritePin(GPIOA, 4, GPIO_PIN_SET);//stop g2		
		GPIO_WritePin(GPIOA, 1, GPIO_PIN_RESET);//start y2
//		ms_delay(2000);

		for (i=0; i<mode.yellow/6000; i++)
		{
			x = trafficGenerator();
			
			for (j=0; j<x; j++)
			{
				int a = white[0][j].Port;
				uint16_t b = white[0][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
			}
			
			int y = trafficGenerator();
			
			for (j=0; j<y; j++)
			{
				int a = white[1][j].Port;
				uint16_t b = white[1][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
			}			
			
			for (j=0; j<6000/600; j++)
			{
				for (k=0; k<3; k++)
				{
					int a = white2[0][k].Port;
					uint16_t b = white2[0][k].Pin;
					int c = white2[1][k].Port;
					uint16_t d = white2[1][k].Pin;
					GPIO_WritePin(Find_Port(a),b, GPIO_PIN_RESET);
					GPIO_WritePin(Find_Port(c),d, GPIO_PIN_RESET);					
					ms_delay(200);
					GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
					GPIO_WritePin(Find_Port(c),d, GPIO_PIN_SET);
				}
			}
			for (j=0; j<x; j++)
			{
				int a = white[0][j].Port;
				uint16_t b = white[0][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
			}
			for (j=0; j<y; j++)
			{
				int a = white[1][j].Port;
				uint16_t b = white[1][j].Pin;
				GPIO_WritePin(Find_Port(a),b, GPIO_PIN_SET);
			}
			if (x<3 && y<3)
				mode = delayed;
			else 
				mode = normal;
		}

		GPIO_WritePin(GPIOA, 1, GPIO_PIN_SET);//stop y2
		GPIO_WritePin(GPIOA, 5, GPIO_PIN_SET);//stop r1

	}	
}

