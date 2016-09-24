/******************************************************************************
 *                                                                            *
 *  FileName            : Semaphore.h	                                      *
 *  Date                : June 2013                                           *
 *  Description         : Semaphor data structure	                          *
 *                                                                            *
 ******************************************************************************/

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include "Queue.h"

// Semaphore structure stores counter value and pointer to the
// tasks of this semaphore
typedef struct Semaphore
{
	int Value;
	pQueue Tasks;
}semaphore, * pSemaphore;

#pragma used+

// Semaphore Up operation
// Increases semaphore Value and if it is positive or zero wakes up a
// task from queue
void Up(pSemaphore sem);

// Semaphore Wait operation
// decrease semaphore value and if it is negative block task
void Wait(pSemaphore sem);

#pragma used-

#endif

