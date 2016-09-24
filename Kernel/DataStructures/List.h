/******************************************************************************
 *                                                                            *
 *  FileName            : List.h		                                      *
 *  Date                : May 2013                                            *
 *  Description         : Tow way linked list                                 *
 *                                                                            *
 ******************************************************************************/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

// Node stores pointer to Next and Previuse nodes in linked list
// and data item.
typedef struct ListNode
{
    struct ListNode* Next;      // Pointer to Next Node
    struct ListNode* Prev;      // Pointer to Previous Node
    void* Data;             // Pointer to Data
}listNode, *pListNode;

// Linked list stores Header and Tailer     
typedef struct LinkedList
{
    pListNode Header;           // Pointer to Header
    pListNode Tailer;           // Pointer to Tailer
}linkedList, *pLinkedList;

// Comparer function pointer
typedef char (*pSortFunc)(pListNode left, pListNode right);

#pragma used+

/*
// Creating LinkedList in heap and return a Pointer to it
// if not enough memory available returns null
pLinkedList CreateLinkedList(void);

// Delete all nodes and free LinkedList from memory
void FreeLinkedList(pLinkedList list);

// Allocate a node with the given data
// if not enough memory available returns null
pListNode CreateListNode(void *Data);
*/

// Add a nede at given index of location to the list
// if locaton was negative or out of range returns 0
// if successfully inserted returns 1
char AddListNodeAt(int loc, pLinkedList list, pListNode newNode);

// Delete a node at given index of location of list
// if index was out of range returns 0
// else if succeed returns 1
char DeleteListNodeAt(int loc, pLinkedList list);

// Returns number of nodes in list
int LengthOfLinkedList(pLinkedList list);

// Remove a node at index and returne that node
// and dosen't delete or free allocated memory
pListNode RemoveListNodeAt(int loc, pLinkedList list);

// Sort the given linked list
// Give a pointer to sort comparer function
void SortLinkedList(pLinkedList list, pSortFunc SortFunc);

// Add node in sorted list
char AddListNodeToSortedList(pLinkedList list, pListNode newNode, pSortFunc sortFunc);

#pragma used-

#endif
 
