/******************************************************
 *                                                    *
 *  FileName            : UserTasks.c		          *
 *  Date                : June 2013                   *
 *  Description         : User defined tasks	 	  *
 *                                                    *
 ******************************************************/

#include <stdio.h>
#include <delay.h>

#include "Context.h"
#include "TaskManagement.h"

UBYTE Task1_DSTK[DATA_STACK_SIZE];
UBYTE Task1_HSTK[HARDWARE_STACK_SIZE];

void TASK1(void)
{
    volatile float a ,b ,res;
    a = 5.2;
    b = 4.8;
    while(1)
    {
        res = 1;       
        res = a + b;
        if(res == (5.2 + 4.8)) // FLOAT OK
        {
            PORTB.2 = 1;
            ENTER_CRITICAL
            {
                printf("res : %f\r" ,res);
            }
           EXIT_CRITICAL
        }
        else
        {
            PORTB.2 = 0;
        }      
        
        Sleep(5);    
        
        PORTB.1 ^=1; 
        ENTER_CRITICAL
        {
            printf("\r\r          =============\r"
                           "          ===  Math ===\r"
                           "          =============\r\r");  
        }
        EXIT_CRITICAL
    }
}

UBYTE Task2_DSTK[DATA_STACK_SIZE];
UBYTE Task2_HSTK[HARDWARE_STACK_SIZE];

void TASK2(void)
{
    while(1)
    {
        PORTB.3 ^= 1;
        //Sleep(10);
        delay_ms(250);
    }
}

pTcb CreateTask1(void)
{
	return CreateTask(TASK1, Task1_HSTK, Task1_DSTK, 100);
}

pTcb CreateTask2(void)
{
	return CreateTask(TASK2, Task2_HSTK, Task2_DSTK, 50);
}
