/******************************************************************************
 *                                                                            *
 *  FileName            : Scheduler.h	                                      *
 *  Date                : June 2013                                           *
 *  Description         : Scheduler implementation	                          *
 *                                                                            *
 ******************************************************************************/
 
#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "Config.h"
#include "List.h"
#include "TaskControlBlock.h"

#pragma used+

// Add the created task to ready list
pTcb AddTaskToReadyList(pTcb task);

// Remove the task from ready list
pListNode RemoveTaskFromReadyList(pTcb task);

// Add ListNode to slept list
char AddListNodeToSleptList(pListNode node);

// Add ListNode to slept list
char AddListNodeToBlockedList(pListNode node);

// Remove task from slept list and add to ready list
pListNode RemoveTaskFromSleptList(pTcb task);

// Remove task from blocked list 
pListNode RemoveTaskFromBlockedList(pTcb task);

// Add ListNode to ready list
char AddListNodeToReadyList(pListNode node);

#pragma used-

// NULL_TASK create
pTcb CreateNullTask(void);

#endif

