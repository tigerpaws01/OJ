#include <cstdio>
#include <iostream>
#include <stdlib.h>

//#define DEBUG

using namespace std;

struct Node{
	char c;
	Node * prev;
	Node * next;
};

Node *cursor;

void Print(Node *head);

Node* NewNode(char c)
{
	Node * newNode =(Node*)malloc(sizeof(Node));
	newNode->c = c;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void Insert(char c)
{
	Node *newNode;
	newNode = NewNode(c);
	//printf("Set newNode as %c\n", c);
	newNode->prev = cursor;
	//printf("Set newnode prev as %c\n", cursor->c);
	newNode->next = cursor->next;
	//if(cursor->next != NULL)printf("Set newnode next as %c\n", cursor->next->c);
	//else printf("Set newnode next as NULL\n");
	if(cursor->next != NULL) cursor->next->prev = newNode;
	cursor->next = newNode;
	//Print(cursor);
	cursor = newNode;
}

void Delete(Node *c)
{
	if(c->prev == NULL) return;
	//printf("Deleted (%c)", c->c);
	Node *toD = c;
	c->prev->next = c->next;
	if(c->next != NULL)c->next->prev = c->prev;
	cursor = c->prev;
	free(toD);
}

int inLinePosition(Node *c)
{
	Node *test = c;
	int result = 0;
	if(c->prev == NULL || c->c == '\n') return 0;
	while(test->prev != NULL && test->c != '\n') test = test->prev;
	for(;test != c;test = test->next, result++);
	return result;
}

// process special characters
void Process(char c)
{
	int p;
	Node *test;
	switch(c)
	{
		case 'u':
			p = inLinePosition(cursor);
			test = cursor;
			while(test->c != '\n' && test->prev != NULL) test = test->prev;
			if(test->prev == NULL) break;
			else
			{
				test = test->prev;
				while(test->c != '\n' && test->prev != NULL) test = test->prev;
				for(;p-- && test->next != NULL && test->next->c != '\n';) test = test->next;
				cursor = test;
			}
			break;
		case 'd':
			p = inLinePosition(cursor);
			test = cursor;
			if(p == 0 && test->next != NULL) test=test->next;
			while(test->c != '\n' && test->next != NULL) test=test->next;
			if(test->next == NULL) break;
			else
			{
				 for(;p-- && test->next != NULL && test->next->c != '\n';) test = test->next;
				 cursor = test;
			}
			break;
		case 'l':
			if(cursor->prev != NULL && cursor->c != '\n') cursor = cursor->prev;
			break;
		case 'r':
			if(cursor->next != NULL && cursor->next->c != '\n') cursor = cursor->next;
			break;
		case 'b':
			if(cursor->prev == NULL || cursor->c == '\n') break;
			Delete(cursor);
			break;
		case 'n':
			if(cursor->c == '\n' && cursor->next != NULL) cursor=cursor->next;
			while(cursor->c != '\n' && cursor->next != NULL) cursor=cursor->next;
			Node *newNode;
			newNode = NewNode('\n');
			newNode->next = cursor->next;
			newNode->prev = cursor;
			if(cursor->next != NULL) cursor->next->prev = newNode;
			cursor->next = newNode;
			break;
		case 'e':
			if(cursor->c == '\n' && cursor->next != NULL) cursor=cursor->next;
			while(cursor->c != '\n' && cursor->next != NULL) cursor=cursor->next; // delete this line
			Delete(cursor);
			while(cursor->c != '\n' && cursor->c != '*') Delete(cursor);
			if(cursor->next != NULL)
			{
				cursor=cursor->next;
				if(cursor->c == '\n') cursor = cursor->prev;
				else while(cursor->next != NULL && cursor->next->c != '\n') cursor=cursor->next;
			}
			else if(cursor->prev != NULL)
				cursor=cursor->prev;
			else
	 		{
				cursor->next = NewNode('\n');
				cursor->next->prev = cursor;
			}
	}
}

#ifdef DEBUG
void PrintDebug(Node *head)
{
	Node* toD = head;
	cout << "##################\n";
	if (head == cursor)
		cout << '^';
	head = head->next;
	while(head != NULL)
	{
		toD = head;
		cout << head->c;
		if (head == cursor)
			cout << '^';
		if(head->c != '\n' && head->next == NULL) cout << '\n';
		head = head->next;

		//free(toD);
	}
	cout << "##################";
	puts("");
}
#endif

void Print(Node *head)
{
	Node* toD = head;
	head = head->next;
	free(toD);
	while(head != NULL)
	{
		toD = head;
		cout << head->c;
		if(head->c != '\n' && head->next == NULL) cout << '\n';
		head = head->next;

		free(toD);
	}
}

int main()
{
	char c;
	Node *head = NewNode('*');
	head->next = NewNode('\n');
	head->next->prev = head;
	cursor = head;
	while(scanf("%c", &c) != EOF)
	{
		switch(c)
		{
			case '/':
				scanf("%c", &c);
				Process(c);
				#ifdef DEBUG
				PrintDebug(head);
				#endif
				break;
			case '\n':
				break;
			default:
				Insert(c);
				#ifdef DEBUG
				PrintDebug(head);
				#endif
		}
	}
	Print(head);
	return 0;
}
