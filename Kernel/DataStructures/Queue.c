/******************************************************************************
 *                                                                            *
 *  FileName            : Queue.c		                                      *
 *  Date                : June 2013                                           *
 *  Description         : Queue data structure                                *
 *                                                                            *
 ******************************************************************************/

#include <stdlib.h>
#include "Queue.h"
 
// Add the new node to the queue list
// If succeed retern 1 else returns 0
char Enqueue(pQueueNode newNode, pQueue queueList)
{
	// First node
	if (LengthOfQueue(queueList) == 0)
	{
		queueList->Header = newNode;
		queueList->Header = queueList->Rear;
	}
	else
	{
		queueList->Rear->Next = newNode;
		queueList->Rear = newNode;
	}
	
	return 1;
}

// Dequeue the first queue node from head of queue
// Returns pointer to dequeued node to caller
// if queue is empty return null pointer 
pQueueNode Dequeue(pQueue queueList)
{
	pQueueNode head;
	int size = LengthOfQueue(queueList);

	// Queue is empty
	if (size == 0)
		return NULL;
	
	head = queueList->Header;
	
	// Last node in the queue
	if (size == 1)
		queueList->Header = queueList->Rear = NULL;
	else
		queueList->Header = queueList->Header->Next;
	
	head->Next = NULL;
	return head;
}

// Length of Queue
int LengthOfQueue(pQueue queueList)
{
	int len = 0;
	pQueueNode nextNode = queueList->Header;
	
	while (nextNode)
	{
		nextNode = nextNode->Next;
		++len;
	}
	
	return len;
}

