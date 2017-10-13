#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include "function.h"
using namespace std;

Node * head;

void printNode(Node* head);

void _insert(Node *&sequence, long data, int power)
{
	Node * s = sequence;
	// When the sequence is empty
	if(s == NULL)
	{
		//printf("  Sequence is empty\n");
		sequence = (Node*)malloc(sizeof(Node));
		sequence->data = data;
		sequence->power = power;
		sequence->next = NULL;
		sequence->prev = NULL;
		return;
	}
	// Insert in the front of the sequence
	if(s->power < power)
	{
		//printf("  Front of it\n");
		sequence->prev =(Node*)malloc(sizeof(Node));
		sequence->prev->next = sequence;
		sequence->prev->data = data;
		sequence->prev->power = power;
		sequence = sequence->prev;
	}
	// Same as the sequence head
	else if (sequence->power == power)
	{
		sequence->data += data;
		return;
	}
	else //s->power > power
	{
		for(;s->next != NULL && s->next->power > power;s = s->next);
		if(s->next == NULL)
		{
			//printf("  To the last\n");
			s->next = (Node*)malloc(sizeof(Node));
			s->next->next = NULL;
			s->next->prev = s;
			s->next->data = data;
			s->next->power = power;
		}
		else
		{
			if(s->next->power == power)
			{
				//printf("  Existed!\n");
				s->next->data += data;
			}
			else // s->next->power < power
			{
				Node * newNode = (Node*)malloc(sizeof(Node));
				newNode->data = data;
				newNode->power = power;
				newNode->next = s->next;
				newNode->prev = s;
				s->next->prev = newNode;
				s->next = newNode;
			}
		}
	}
	
	
}

void printNode(Node* head)         //the function which will print the output
{
	while(head != NULL)
	{
		if(head->data == 0)
		{
			head = head->next; continue;
		}
		cout << " " << head->data << " " << head->power;
		head = head->next;
	}
}
Node* create()                     //create polynomial linked list
{
	long data;
	int power;
	head = (Node*)malloc(sizeof(Node));
	
	head->next = NULL;
	head->prev = NULL;
	Node * cur = head;
	while(1)
	{
		int d, p;
		cin >> d >> p;
		cur->data = d;
		cur->power = p;
		
		if(cur->power == 0) break;
		
		cur->next = (Node*)malloc(sizeof(Node));
		cur->next->next = NULL;
		cur->next->prev = cur;
		cur = cur->next;
	}
	//cout << head->data << "\n";
	return head;
}
void destroy(Node *node)           //destroy polynomial linked list
{
	Node * cur = node;
	while(cur != NULL)
	{
		Node * toD = cur;
		cur = cur->next;
		free(toD);
	}
}
Node* multiple(Node* p1, Node* p2) //input two polynomial linked list and return the result
{
	Node * resultHead = NULL;
	Node * curP1 = p1, *curP2 = p2;
	for(;curP1 != NULL;curP1 = curP1->next)
	{
		curP2 = p2;
		for(;curP2 != NULL;curP2 = curP2->next)
		{
			//printf("Ins: %dx^%d\n", curP1->data*curP2->data, curP1->power+curP2->power);
			_insert(resultHead, curP1->data*curP2->data, curP1->power+curP2->power);
			//printNode(resultHead);
		}
	}
	return resultHead;
}
