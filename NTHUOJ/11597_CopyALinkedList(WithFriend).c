#include <stdlib.h>
#include "function.h"
#define D 20

unsigned long lengthOf(Node *src)
{
	while(src->next != NULL) src = src->next;
	return src->id + 1;
}

Node* copy(Node *src)
{
	Node *srcCur = src, *headCur, *head, *temp, *halfway[D];
	unsigned long halfwayID[D];
	
	unsigned long i = 0;
	// Set ID of src
	for(;srcCur != NULL;srcCur = srcCur->next)
		srcCur->id = i++;
		
	// Build a list just like src
	unsigned long l = lengthOf(src), length;
	length = l;
	
	head=(Node*)malloc(sizeof(Node));
	temp=head;
	for(i=0;l--;)
	{
		temp->next=(Node*)malloc(sizeof(Node));
		temp=temp->next;
		int k;
		for(k=0; k<D; k++) if(i <=(k*length/D)) halfway[k] = temp, halfwayID[k] = i;
		temp->id = i++;
		temp->fri=NULL;
	}
	temp->next=NULL;
	temp=head->next;
	free(head);
	head=temp;

	// Simulate friend
	srcCur = src, headCur = head;
	for(;srcCur != NULL && headCur != NULL; srcCur = srcCur->next, headCur = headCur->next)
	{
		if(srcCur->fri == NULL) continue;
		Node *setMeFri;
		int k;
		for(k=0; k<D && srcCur->fri->id >= halfwayID[k]; k++)  setMeFri = halfway[k];
		for(;setMeFri->id != srcCur->fri->id;setMeFri = setMeFri->next);
		headCur->fri = setMeFri;
	}
	return head;
}
