/******************************************************************************
 *                                                                            *
 *  FileName            : TaskManagement.h                                    *
 *  Date                : June 2013                                           *
 *  Description         : Task management functions                           *
 *                                                                            *
 ******************************************************************************/

#ifndef TASKMANAGEMENT_H_
#define TASKMANAGEMENT_H_

#include "Config.h"
#include "Context.h"
#include "TaskControlBlock.h"

#ifndef _DEBUGING_MODE_
#define DATA_STACK_SIZE		140
#else
#define DATA_STACK_SIZE		140
#endif

#define HARDWARE_STACK_SIZE	85

#define OS_TASK_RUNNABLE	0b00000000
#define OS_TASK_RUNNING		0b00000001
#define OS_TASK_DELAYED		0b00000010
#define OS_TASK_BLOCKED		0b00000100

#pragma used+

// Create a task
// Initialize task data and hardware stacks.
pTcb CreateTask(void(*task)(void), UBYTE* HWstk, UBYTE* Dstk, UBYTE Priority);

// Sleep the current task for the given tick period.
void Sleep(UWORD ticks);

// Sleep the given task for the specified ticks period.
void SleepTask(pTcb task, UWORD ticks); 

// Wakeup task and add to ready list
void WakeupTask(pTcb task);

// Incease reset counter by one.
// This function must be used after reseting or powering on the cpu.
void IncreaseResetCounter(void);

// Get reset counter value.
unsigned long GetResetCounter(void);

// Blocks the current task
void Block(void);

// Blocks the given task
void BlockTask(pTcb task);

// Resume the given task
void ResumeTask(pTcb task);

#pragma used-

#endif

