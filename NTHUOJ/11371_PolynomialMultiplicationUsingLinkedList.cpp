#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "function.h"
using namespace std;


void printNode(Node* head)
{
	for(;head != NULL;head = head->next)	
		if(head->data != 0) cout << " " << head->data << " " << head->power;
}

Node* create()
{
	Node *head = (Node*)malloc(sizeof(Node)), *temp;
	temp = head;
	while(1)
	{
		cin >> temp->data >> temp->power;
		temp->next = NULL;
		if(temp->power == 0) break;
		
		temp->next = (Node*)malloc(sizeof(Node));
		temp->next->prev = temp;
		temp = temp->next;
	}
	return head;
}
void destroy(Node *node)
{
	while(node != NULL)
	{
		Node *tod = node;
		node = node->next;
		free(tod);
	}
}

void _insert(Node *&head, long data, int power)
{
	Node *cur = head;
	if(cur == NULL)
	{
		head =(Node*)malloc(sizeof(Node));
		head->data = data;
		head->power = power;
		head->next = NULL;
		head->prev = NULL;
	}
	else if(power > cur->power)
	{
		head->prev = (Node*)malloc(sizeof(Node));
		head->prev->prev = NULL;
		head->prev->next = head;
		head->prev->power = power;
		head->prev->data = data;
		head = head->prev;
	}
	else if(power == cur->power)
	{
		head->data += data;
	}
	else // power < cur->power
	{
		for(;cur->next != NULL && power < cur->next->power; cur = cur->next);
		if(cur->next == NULL)
		{
			cur->next = (Node*)malloc(sizeof(Node));
			cur->next->next = NULL;
			cur->next->prev = cur;
			cur->next->data = data;
			cur->next->power = power;
		}
		else if(power == cur->next->power)
		{
			cur->next->data += data;
		}
		else // power > cur->next->power
		{
			Node *newNode = (Node*)malloc(sizeof(Node));
			newNode->data = data;
			newNode->power = power;
			newNode->prev = cur;
			newNode->next = cur->next;
			cur->next->prev = newNode;
			cur->next = newNode;
		}
	}
}

Node* multiple(Node* p1, Node* p2)
{
	Node *cur1, *cur2, *resultHead = NULL;
	
	for(cur1 = p1; cur1 != NULL; cur1 = cur1->next)
	for(cur2 = p2; cur2 != NULL; cur2 = cur2->next)
		_insert(resultHead, cur1->data*cur2->data, cur1->power+cur2->power);
	return resultHead;
}
