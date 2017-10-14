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
	// Build a linked list of the same size with src
	unsigned long l = lengthOf(src);
	Node *head=(Node*)malloc(sizeof(Node));
	Node *temp=head;
	Node *halfway[D];
	unsigned long i, halfwayID[D];
	
	for(i=0;i<l;)
	{
		temp->next=(Node*)malloc(sizeof(Node));
		temp=temp->next;
		int k = 1;
		for(;k<D;k++) if(i <= k*(l-1)/D) {halfway[k] = temp; halfwayID[k] = i;}
		temp->id=i++;
		temp->fri=NULL;
		
		//if(i == l/2) halfway = temp, halfwayID = i;
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
		//Node * setMeUrFriend = (srcCur->fri->id >= halfwayID ? halfway : head);
		Node * setMeUrFriend;
		int k;
		for(k = 0;k<D && srcCur->fri->id >= halfwayID[k] ;k++)
		{
			setMeUrFriend = halfway[k];
		}
		//unsigned long i = 0;
		for(;setMeUrFriend->id != srcCur->fri->id;setMeUrFriend = setMeUrFriend->next);
		//for(;i - srcCur->fri->id;setMeUrFriend = setMeUrFriend->next, i++);
		resultCur->fri = setMeUrFriend;
	}
	return head;
}
