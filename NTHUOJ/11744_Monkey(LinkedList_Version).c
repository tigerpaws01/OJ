#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	char data;
	struct _node *next, *prev;
} Node;

Node* NewNode(char data)
{
	Node *n = (Node*)malloc(sizeof(Node));
	n->data = data;
	n->next = n->prev = NULL;
	return n;
}
void Insert(Node *pos, char data, Node **head)
{
	Node *n = NewNode(data);
	// Attach
	n->next = pos;
	n->prev = pos->prev;
	if(pos->prev != NULL) pos->prev->next = n;
	pos->prev = n;
	
	// Modify head pointer when needed
	if(n->prev == NULL) (*head) = n;
}

void Delete(Node **pos, Node **head)
{
	// Assertion
	Node *cur = *pos, *d = *pos;
	if(cur->next == NULL) return;
	// Detach
	if(cur->prev != NULL) cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	// Modify head pointer when needed
	if(*pos == *head) *head = cur->next;
	// Move cursor
	*pos = cur->next;
	
	// Deallocate
	free(d);
}

void LeftShift(Node **cursor)
{
	if((*cursor)->prev == NULL) return;
	*cursor = (*cursor)->prev;
}

void RightShift(Node **cursor)
{
	if((*cursor)->next == NULL) return;
	*cursor = (*cursor)->next;
}

void Print(Node *head)
{
	Node *cur = head;
	while(cur != NULL)
		putchar(cur->data), cur = cur->next;
}

void Free(Node *head)
{
	Node *cur = head;
	while(cur != NULL)
	{
		Node *d = cur;
		cur = cur->next;
		free(d);
	}
}

int main(){
	// Creating a tail node ensures simpler operations when inserting and deleting.
	// Cursor is in FRONT of the node it points to.
	Node *head = NewNode('\n'), *cursor = head;
	char c;
	while(~scanf(" %c", &c))
	{
		if(c == '>')
			RightShift(&cursor);
		else if(c == '<')
			LeftShift(&cursor);
		else if(c == 'D')
			Delete(&cursor, &head);
		else
			Insert(cursor, c, &head);
	}
	
	Print(head);
	Free(head);
	return 0;
}
