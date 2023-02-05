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
traffic mode;
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

lane Vertical, Horizontal;

GPIO_TypeDef *Find_Port(int Port_no)
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
	return rand() % 3 + 1;
}
void handle_traffic(lane a, lane b)
{
		int i, j, k, x, y;

		GPIO_WritePin(Find_Port(a.Green.Port), a.Green.Pin, GPIO_PIN_RESET); // start g1
		GPIO_WritePin(Find_Port(b.Red.Port), b.Red.Pin, GPIO_PIN_RESET); // start r2
		//		ms_delay(3000);

		mode = normal;
	
		for (i = 0; i < mode.green / 6000; i++)
		{
			x = trafficGenerator();

			for (j = 0; j < x; j++)
					GPIO_WritePin(Find_Port(b.White[0][j].Port), b.White[0][j].Pin, GPIO_PIN_RESET);
			
			y = trafficGenerator();

			for (j = 0; j < y; j++)
				GPIO_WritePin(Find_Port(b.White[1][j].Port), b.White[1][j].Pin, GPIO_PIN_RESET);
			
			for (j = 0; j < 6000 / 600; j++)
			{
				for (k = 0; k < 3; k++)
				{
					GPIO_WritePin(Find_Port(a.White[0][k].Port), a.White[0][k].Pin, GPIO_PIN_RESET);
					GPIO_WritePin(Find_Port(a.White[1][k].Port), a.White[1][k].Pin, GPIO_PIN_RESET);
					ms_delay(200);
					GPIO_WritePin(Find_Port(a.White[0][k].Port), a.White[0][k].Pin, GPIO_PIN_SET);
					GPIO_WritePin(Find_Port(a.White[1][k].Port), a.White[1][k].Pin, GPIO_PIN_SET);
				}
			}
			for (j = 0; j < x; j++)
					GPIO_WritePin(Find_Port(b.White[0][j].Port), b.White[0][j].Pin, GPIO_PIN_SET);
			
			for (j = 0; j < y; j++)
				GPIO_WritePin(Find_Port(b.White[1][j].Port), b.White[1][j].Pin, GPIO_PIN_SET);
			
		}

		GPIO_WritePin(Find_Port(a.Green.Port), a.Green.Pin, GPIO_PIN_SET);	 // stop g1
		GPIO_WritePin(Find_Port(a.Yellow.Port), a.Yellow.Pin, GPIO_PIN_RESET); // start y1
		//		ms_delay(2000);

		for (i = 0; i < mode.yellow / 6000; i++)
		{
			x = trafficGenerator();

			for (j = 0; j < x; j++)
					GPIO_WritePin(Find_Port(b.White[0][j].Port), b.White[0][j].Pin, GPIO_PIN_RESET);
			
			y = trafficGenerator();

			for (j = 0; j < y; j++)
				GPIO_WritePin(Find_Port(b.White[1][j].Port), b.White[1][j].Pin, GPIO_PIN_RESET);
			
			for (j = 0; j < 6000 / 600; j++)
			{
				for (k = 0; k < 3; k++)
				{
					GPIO_WritePin(Find_Port(a.White[0][k].Port), a.White[0][k].Pin, GPIO_PIN_RESET);
					GPIO_WritePin(Find_Port(a.White[1][k].Port), a.White[1][k].Pin, GPIO_PIN_RESET);
					ms_delay(200);
					GPIO_WritePin(Find_Port(a.White[0][k].Port), a.White[0][k].Pin, GPIO_PIN_SET);
					GPIO_WritePin(Find_Port(a.White[1][k].Port), a.White[1][k].Pin, GPIO_PIN_SET);
				}
			}
			for (j = 0; j < x; j++)
					GPIO_WritePin(Find_Port(b.White[0][j].Port), b.White[0][j].Pin, GPIO_PIN_SET);
			
			for (j = 0; j < y; j++)
				GPIO_WritePin(Find_Port(b.White[1][j].Port), b.White[1][j].Pin, GPIO_PIN_SET);
			
		}

		GPIO_WritePin(Find_Port(a.Yellow.Port), a.Yellow.Pin, GPIO_PIN_SET);	 // stop y1
		GPIO_WritePin(Find_Port(b.Red.Port), b.Red.Pin, GPIO_PIN_SET); // stop r2
		//		ms_delay(2000);
}
void init_pins()
{

	Vertical.Green.Port = A;
	Vertical.Green.Pin = 7;
	Vertical.Yellow.Port = A;
	Vertical.Yellow.Pin = 6;
	Vertical.Red.Port = A;
	Vertical.Red.Pin = 5;
	Vertical.White[0][0].Port = B;
	Vertical.White[0][0].Pin = 1;
	Vertical.White[0][1].Port = B;
	Vertical.White[0][1].Pin = 2;
	Vertical.White[0][2].Port = B;
	Vertical.White[0][2].Pin = 5;
	Vertical.White[1][0].Port = B;
	Vertical.White[1][0].Pin = 8;
	Vertical.White[1][1].Port = B;
	Vertical.White[1][1].Pin = 7;
	Vertical.White[1][2].Port = B;
	Vertical.White[1][2].Pin = 6;

	Horizontal.Green.Port = A;
	Horizontal.Green.Pin = 4;
	Horizontal.Yellow.Port = A;
	Horizontal.Yellow.Pin = 1;
	Horizontal.Red.Port = A;
	Horizontal.Red.Pin = 0;
	Horizontal.White[0][0].Port = A;
	Horizontal.White[0][0].Pin = 12;
	Horizontal.White[0][1].Port = A;
	Horizontal.White[0][1].Pin = 11;
	Horizontal.White[0][2].Port = B;
	Horizontal.White[0][2].Pin = 0;
	Horizontal.White[1][0].Port = A;
	Horizontal.White[1][0].Pin = 8;
	Horizontal.White[1][1].Port = A;
	Horizontal.White[1][1].Pin = 9;
	Horizontal.White[1][2].Port = A;
	Horizontal.White[1][2].Pin = 10;	
}
int main(void)
{
	//    srand(time(0));
	
	init_pins();
	
	traffic mode = normal;

	initClock();
	sysInit();

	GPIO_InitTypeDef z;

	GPIO_Init(GPIOA, &z);
	GPIO_Init(GPIOB, &z);

	while (1)
	{
		handle_traffic(Vertical, Horizontal);
		handle_traffic(Horizontal, Vertical);

	}
}
