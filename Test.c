#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

enum
{
    A,
    B,
    C
};

typedef struct
{
    int Port;
    int Pin;
} PortPin;

PortPin white[2][3] = {{{A, 6}, {A, 9}, {A, 10}}, {{A, 11}, {B, 5}, {B, 10}}};

void Find_Port(int Port_no)
{
    if (Port_no == A)
        printf("GPIOA\n");
    else if (Port_no == B)
        printf("GPIOB\n");
    else if (Port_no == C)
        printf("GPIOC\n");
}
int main()
{
    srand(time(0));

    while (1)
    {
        int x = rand() % 3 + 1;
        printf("%d\n", x);

        for (int i = 0; i < x; i++)
        {
            int a = white[0][i].Port;
            int b = white[0][i].Pin;
            printf("Port: ");
            Find_Port(a);
            printf("Pin: %d\n", b);
        }

        delay(1);
    }
}