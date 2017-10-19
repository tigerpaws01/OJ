#include <stdlib.h>
#include "function.h"
#define D 20

unsigned long lengthOf(Node *head)
{
	for(;head->next != NULL;head = head->next);
	return head->id+1;
}

Node* copy(Node *src)
{
	// Set ID for src
	Node *srcIDSet = src;
	unsigned long srcID = 0;
	while(srcIDSet != NULL)
	{
		srcIDSet->id = srcID++;
		srcIDSet = srcIDSet->next;
	}
	unsigned long l = lengthOf(src);
	// Build a linked list of the same size with src
	
	unsigned long length = l;
	Node *halfway[D];
	unsigned long i, halfwayID[D];
	
	Node *head=malloc(sizeof(Node));
	Node *temp=head;
	for(unsigned long i=0;l--;)
	{
		
		temp->next=malloc(sizeof(Node));
		temp=temp->next;
		int indicator;
		for(indicator = 0; indicator<D; indicator++) if(i <= (indicator*length/D)) halfway[indicator] = temp, halfwayID[indicator] = i;
		temp->id = i++;
		temp->fri=NULL;
		
	}
	temp->next=NULL;
	temp=head->next;
	free(head);
	head=temp;

	halfway[0] = head;
	halfwayID[0] = head->id;

	Node *srcCur = src, *resultCur = head;
	for(;srcCur != NULL; srcCur = srcCur->next, resultCur = resultCur->next)
	{
		if(srcCur->fri == NULL) {
			resultCur->fri = NULL; continue;
		}
		Node * setMeUrFriend;
		int k;
		for(k = 0;k<D && srcCur->fri->id >= halfwayID[k] ;k++)
		{
			setMeUrFriend = halfway[k];
		}
		for(;setMeUrFriend->id != srcCur->fri->id;setMeUrFriend = setMeUrFriend->next);
		resultCur->fri = setMeUrFriend;
	}
	return head;
}
