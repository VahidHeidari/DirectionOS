/******************************************************************************
 *                                                                            *
 *  FileName            : Semaphore.c	                                      *
 *  Date                : June 2013                                           *
 *  Description         : Semaphor data structure	                          *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
 
#include "Semaphore.h"
#include "Context.h"

// Semaphore Up operation
// Increases semaphore Value and if it is positive or zero wakes up a
// task from queue
void Up(pSemaphore sem)
{
	ENTER_CRITICAL;
	{
		if (++sem->Value <= 0)
		{
			pQueueNode task;
			task = Dequeue(sem->Tasks);
			if (task)
			{
				// Wake up task
				/// TODO
			}
		}
	}
	EXIT_CRITICAL;
}

// Semaphore Wait operation
// decrease semaphore value and if it is negative block task
void Wait(pSemaphore sem)
{
	ENTER_CRITICAL;
	{
		if (--sem->Value < 0)
		{
			pQueueNode task;
			
			/// TODO
			task = NULL;
			// Add task to blocked list
			Enqueue(task, sem->Tasks);
		}
	}
	EXIT_CRITICAL;
}

