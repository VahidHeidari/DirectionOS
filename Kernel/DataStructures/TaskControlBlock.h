/******************************************************************************
 *                                                                            *
 *  FileName            : TaskControlBlock.h                                  *
 *  Date                : June 2013                                           *
 *  Description         : Task Control structures                             *
 *                                                                            *
 ******************************************************************************/

#ifndef TASK_CONTROL_BLOCK_H_
#define TASK_CONTROL_BLOCK_H_

typedef unsigned char UBYTE;
typedef unsigned long int UWORD;

typedef struct TaskControlBlock
{
	void* DataStack;
	void* HwStack;
	UBYTE Status;
	UWORD Delay;
    UBYTE Priority;
}tcb, * pTcb;

#endif

