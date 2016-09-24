/******************************************************************************
 *                                                                            *
 *  FileName            : Queue.h		                                      *
 *  Date                : June 2013                                           *
 *  Description         : Queue data structure                                *
 *                                                                            *
 ******************************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_

// Queue node structure
// Node stores pointers to the next node and its data item
typedef struct QueueNode
{
	struct QueueNode* Next;		// Next node in queue
	void* Data;					// Data item
}queueNode, * pQueueNode;

// Queue structure stores pointers to the head and rear of queue
typedef struct QueueTag
{
	pQueueNode Header;			// Head of queue
	pQueueNode Rear;			// Rear of queue
}queueStruct, * pQueue;

#pragma used+

// Add the new node to the queue list
// If succeed retern 1 else returns 0
char Enqueue(pQueueNode newNode, pQueue queueList);

// Dequeue the first queue node from head of queue
// Returns pointer to dequeued node to caller 
pQueueNode Dequeue(pQueue queueList);

// Length of Queue
int LengthOfQueue(pQueue queueList);

#pragma used-

#endif

