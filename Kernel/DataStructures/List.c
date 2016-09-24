/******************************************************************************
 *                                                                            *
 *  FileName            : LinkedList.c                                        *
 *  Date                : May 2013                                            *
 *  Description         : Tow way linked list                                 *
 *                                                                            *
 ******************************************************************************/

#include <stdlib.h>
#include "List.h"

/*
pLinkedList CreateLinkedList(void)
{
    return (pLinkedList)malloc(sizeof(linkedList));
}

void FreeLinkedList(pLinkedList list)
{
    while(DeleteListNodeAt(0,list) != 1)
        continue;
        
    free(list);
}

pListNode CreateListNode(void* Data)
{
    pListNode newNode;
    
    newNode = (pListNode)malloc(sizeof(listNode));
    // If allocated insert data
    if(newNode)
        newNode->Data = Data;
        
    return newNode;
}
*/

char AddListNodeAt(int loc, pLinkedList list, pListNode newNode)
{
    pListNode currNode;
    int i = 0;
    int len = LengthOfLinkedList(list);
    
    // Bad parameters passed to function
    if(loc < 0 || loc > len)
        return 0;
    
    // This is first item in the list    
    if(!list->Header)
    {
        list->Header = list->Tailer = newNode;
        list->Header->Next = list->Header->Prev = NULL;
        return 1;
    }
    
    // End of list
    if(loc == len)
    {
        list->Tailer->Next = newNode;
        newNode->Prev = list->Tailer;
        list->Tailer = newNode;
        return 1;
    }
    
    // Beginning of List
    if(loc == 0)
    {
        list->Header->Prev = newNode;
        newNode->Next = list->Header;
        list->Header = newNode;
        return 1;
    }
    
    // Middel of list
    // Traversing needed
    currNode = list->Header;                // Begginning of List 
    for(i = 0; i < loc; ++i)
        currNode = currNode->Next;          // Traverse to location
            
    newNode->Next  = currNode;
    newNode->Prev  = currNode->Prev;
    currNode->Prev->Next = newNode;
    currNode->Prev = newNode;
            
    return 1;        
}

char DeleteListNodeAt(int loc, pLinkedList list)
{
    pListNode nextNode;    
    int i;
    int len = LengthOfLinkedList(list);
    
    if (loc < 0 || loc >= len)
        return 0;
        
    // Lsat item reminded in the list                               
    if (list->Header == list->Tailer)
    {
        free(list->Header);
        list->Header = list->Tailer = NULL;
        return 1;
    }
    
    // First item in the list
    if (loc == 0)
    {   
        nextNode = list->Header;
        list->Header = list->Header->Next;
        free(nextNode);
        return 1;
    }
    
    // Last item in the list
    if(loc == len)
    {
        nextNode = list->Tailer;
        list->Tailer = list->Tailer->Prev;
        free(nextNode);
        return 1;
    }
    
    // Middel of list
    // Traversing needed
    nextNode = list->Header;          // Beggining of list
    for (i = 0; i < loc; ++i)
        nextNode = nextNode->Next;    // Traversing to location
    nextNode->Prev->Prev = nextNode->Prev;
    nextNode->Prev->Next = nextNode->Next;
    
    free(nextNode);
    
    return 1;
}

int LengthOfLinkedList(pLinkedList list)
{
    int len = 0;
    pListNode nextNode = list->Header;      // Begginig of list
    
    // Traverse List until next pointer isn't null
    while(nextNode)
    {
        nextNode = nextNode->Next;      // Next Node
        ++len;                          // Increase Length of List
    }
    
    return len;   
}

pListNode RemoveListNodeAt(int loc, pLinkedList list)
{
    pListNode rmNode;    
    int i;
    int len = LengthOfLinkedList(list);
    
    if (loc < 0 || loc >= len)
        return (pListNode)0;
        
    // Lsat item reminded in the list                               
    if (len == 1)
    {
        rmNode = list->Header;
        list->Header = list->Tailer = NULL;
    }
    else
        // First item in the list
        if (loc == 0)
        {   
            rmNode = list->Header;
            list->Header = list->Header->Next;
        }
        else
            // Last item in the list
            if(loc == len)
            {
                rmNode = list->Tailer;
                list->Tailer = list->Tailer->Prev;
                return rmNode;
            }
            else
            {
                // Middel of list
                // Traversing needed
                rmNode = list->Header;          // Beggining of list
                for (i = 0; i < loc; ++i)
                    rmNode = rmNode->Next;    // Traversing to location
                rmNode->Prev->Prev = rmNode->Prev;
                rmNode->Prev->Next = rmNode->Next;
            }
	
    rmNode->Next = rmNode->Prev = NULL;
    return rmNode;  
}

#pragma used+
void SwapListNode(pLinkedList list, pListNode lNode, pListNode rNode)
{
	if (lNode == list->Header)
	{
        // Only Header and Tailer are exist in the list
        if (rNode == list->Tailer)
        {
            list->Header->Prev = list->Tailer;
            list->Tailer->Next = list->Header;
            list->Header->Next = list->Tailer->Prev = NULL;
            list->Header = rNode;
            list->Tailer = lNode;
        }
        else
        {
            // Left node is Header and right node isn't Tailer
            list->Header->Prev = rNode;
            list->Header->Next = rNode->Next;
            rNode->Next->Prev = list->Header;
            rNode->Next = list->Header;
            rNode->Prev = NULL;
            list->Header = rNode;    
        }
    }
    else
    {
        // Right node is Tailer and left node isn't Header
        if (rNode == list->Tailer)
        {
            lNode->Prev->Next = list->Tailer;
            list->Tailer->Prev = lNode->Prev;
            lNode->Prev = list->Tailer;
            list->Tailer->Next = lNode;
            lNode->Next = NULL;
            list->Tailer = lNode;	
        }
        else
        {
            // Middel of list
            rNode->Prev = lNode->Prev;
            lNode->Prev->Next = rNode;
                    
            lNode->Next = rNode->Next;
            rNode->Next->Prev = lNode;
                    
            lNode->Prev = rNode;
            rNode->Next = lNode;
        }
    }
}
#pragma used-

void SortLinkedList(pLinkedList list, pSortFunc SortFunc)
{
    int i;
    int j;
    int listSize = LengthOfLinkedList(list);
    for ( i = listSize - 1; i > 0; --i)        
    {
        for (j = 0; j < i; ++j)
        {
        	pListNode lNode = list->Header;
            pListNode rNode;
            int idx = 0;
            
            while (idx < j)
            {
            	lNode = lNode->Next;
            	idx++;    	
            }
            if (lNode->Next)
            	rNode = lNode->Next;	
        	else
            	continue;
                
            if (SortFunc(lNode, rNode))
            {
            	SwapListNode(list, lNode, rNode);    
            }    
        }
    }
}

char AddListNodeToSortedList(pLinkedList list, pListNode newNode, pSortFunc sortFunc)
{
	pListNode rNode = list->Header;
    int index = 0;
	
    while (rNode && sortFunc(newNode, rNode))
    {
    	rNode = rNode->Next;
    	++index;
    }
    return AddListNodeAt(index, list, newNode);
}

