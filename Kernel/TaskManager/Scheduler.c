/******************************************************************************
 *                                                                            *
 *  FileName            : Scheduler.c	                                      *
 *  Date                : June 2013                                           *
 *  Description         : Scheduler implementation	                          *
 *                                                                            *
 ******************************************************************************/
                      
#include "Scheduler.h"
#include "TaskManagement.h"

// Finding index of task in all tcbs list
// if given task there isn't in the ready list, returns -1
#define FindTaskReadyListIndex(task) FindTaskIndex(&ReadyList, task)

// Finding index of task in all tcbs list
// if given task there isn't in the ready list, returns -1
#define FindTaskSleptListIndex(task) FindTaskIndex(&SleptList, task)

// Finding index of task in all tcbs list
// if given task there isn't in the ready list, returns -1
#define FindTaskBlockedListIndex(task) FindTaskIndex(&BlockedList, task)

// Control lists
linkedList ReadyList;
linkedList SleptList;
linkedList BlockedList;

// Lists nodes
listNode AllTasksNodes[MAX_NUM_OF_TASKS];

// Task control blocks
volatile pTcb CurrentTask;
volatile tcb all_tcbs[MAX_NUM_OF_TASKS];
volatile UBYTE totalTasks = 0;

char PrioritySortFunc(pListNode left, pListNode right)
{
	pTcb lTask;
    pTcb rTask;
    
    lTask = (pTcb)left->Data;
    rTask = (pTcb)right->Data;
    
    if (lTask->Priority <= rTask->Priority)
        return 1;
    return 0;
}

void handleDelayedTasks(void)
{
	int i = 0;
    int delayedSize = 0;
    pListNode task;
    pTcb Tcb;
    delayedSize = LengthOfLinkedList(&SleptList);           
    
    if (delayedSize > 0)
	{
    	task = SleptList.Header;
    	while (task)
    	{
        	Tcb = (pTcb)task->Data;
    		Tcb->Delay--;
        	if (Tcb->Delay <= 0)
        	{   
                pListNode node;
                Tcb->Status = OS_TASK_RUNNABLE;
                node = RemoveListNodeAt(i, &SleptList);
                AddListNodeToSortedList(&ReadyList, node, PrioritySortFunc);
            }    
    		++i;
        	task = task->Next;
    	}
	}
}

void selectTask(void)
{
	int readySize = LengthOfLinkedList(&ReadyList);
    
    if (readySize > 0)
    {
    	CurrentTask = (pTcb)ReadyList.Header->Data;
        AddListNodeToSortedList(&ReadyList, RemoveListNodeAt(0, &ReadyList), PrioritySortFunc);
	}
    else
    	#asm("sleep")
}

/*********************************************
 *            N U L L  T A S K               *
 *********************************************/
volatile UBYTE NULL_HSTK[HARDWARE_STACK_SIZE];
volatile UBYTE NULL_DSTK[DATA_STACK_SIZE];

// Defined at Scheduler.c
#ifdef _DEBUGING_MODE_
#include <stdio.h>
extern volatile unsigned long count;
extern volatile char print;
#endif

// Add the created task to ready list
pTcb AddTaskToReadyList(pTcb task)
{   
	pTcb new_task = (pTcb)0;
    
    // Ready list is full
    if (totalTasks < MAX_NUM_OF_TASKS)
	{
        all_tcbs[totalTasks].DataStack 	= task->DataStack;
        all_tcbs[totalTasks].HwStack 	= task->HwStack;
        all_tcbs[totalTasks].Status 	= OS_TASK_RUNNABLE;
        all_tcbs[totalTasks].Delay 		= 0;
        all_tcbs[totalTasks].Priority 	= task->Priority;
                                        
        AllTasksNodes[totalTasks].Data 	= (void*)&all_tcbs[totalTasks];
        
        // Added successfuly
        if (AddListNodeToSortedList(&ReadyList, &AllTasksNodes[totalTasks], PrioritySortFunc) != 0)
        {
            new_task = &all_tcbs[totalTasks];
            ++totalTasks;
        }
    }
    return new_task;
}

// Finding index of task in all tcbs list
// if given task there isn't in the ready list, returns -1
int FindTaskIndex(pLinkedList list, pTcb task)
{
	int i = -1;
	int idx = -1;
	
    pListNode node = list->Header;
    while (node)
    {
    	pTcb t = (pTcb)node->Data;
        ++i;
        if (t == task)
		{
			idx = i;
        	break;
        }
		node = node->Next;
    }
	
    return idx;
}

// Remove the task from slept list
pListNode RemoveTaskFromReadyList(pTcb task)
{
	pListNode rmNode = RemoveListNodeAt(FindTaskReadyListIndex(task), &ReadyList);
	return rmNode;
}

// Add ListNode to slept list
char AddListNodeToSleptList(pListNode node)
{
	return AddListNodeAt(0, &SleptList, node);
}

// Add ListNode to slept list
char AddListNodeToBlockedList(pListNode node)
{
	return AddListNodeAt(0,&BlockedList, node);
}

// Remove task from slept list and add to ready list
pListNode RemoveTaskFromSleptList(pTcb task)
{
	pListNode rmNode = RemoveListNodeAt(FindTaskSleptListIndex(task), &SleptList);
	return rmNode;
}

// Remove task from blocked list 
pListNode RemoveTaskFromBlockedList(pTcb task)
{
	pListNode rmNode = RemoveListNodeAt(FindTaskBlockedListIndex(task), &BlockedList);
	return rmNode;
}

// Add ListNode to ready list
char AddListNodeToReadyList(pListNode node)
{
	return AddListNodeToSortedList(&ReadyList, node, PrioritySortFunc); 
}

/*********************************************
 *           T I M E R  T I C K              *
 *********************************************/
#ifdef _DEBUGING_MODE_
volatile unsigned long count = 0;
volatile char print = 1;
#endif

#pragma savereg-
// Timer 1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{    
    SAVE_CONTEXT();

#ifdef _DEBUGING_MODE_    
    count++;
    print = 1;
#endif
    
    handleDelayedTasks();
    
    selectTask();
    
    RESTORE_CONTEXT();   
}
#pragma savereg+

/*********************************************
 *           N U L L    T A S K              *
 *********************************************/
// NULL_TASK running only when no other runnable task available
void NULL_TASK(void)
{
    while(1)
    {
#ifdef _DEBUGING_MODE_
		if(print)
		{
            ENTER_CRITICAL
            {
                printf("NULL COUNT : %d\r" ,count);
                print = 0;
            }
            EXIT_CRITICAL
		}
#else
		// Simply do nothing
        // BUT can do jobs like memory management, task termination,
        // or sleep cpu.
		#asm("	NOP")
#endif
    }
}

// Creat NULL_TASK and return a pointer to its tcb.
pTcb CreateNullTask(void)
{
	return CreateTask(NULL_TASK ,NULL_HSTK ,NULL_DSTK, 0);
}

