#include "function.h"
#include <stdlib.h>

BTNode* EXPR() // FACTOR | EXPR OP FACTOR; returns the root
{
	//printf("Seek EXPRESSION at %d\n", pos);
	BTNode * f;
	f = FACTOR();
	if(expr[pos] == '&' || expr[pos] == '|')
	{
		BTNode * op = makeNode(expr[pos--]),
					 * e  = EXPR();
		op->left = e;
		op->right = f;
		return op;
	}
	else
	{
		return f;
	}
}
BTNode* FACTOR() // ID | (EXPR)
{
	//printf("Seek FACTOR at %d\n", pos);
	BTNode * n;
	if(expr[pos] == ')')
	{
		//printf("A %c HERE!\n", expr[pos]);
		pos--;
		n = EXPR();
		//printf("A %c HERE!\n", expr[pos]);
		pos--; // '('
	}
	else
	{
		n = makeNode(expr[pos--]);
	}
	return n;
}
BTNode* makeNode(char c)
{
	//printf("Make a node of %c\n", c);
	BTNode * n = (BTNode*) malloc(sizeof(BTNode));
	for(int i = 0; i<6; i++)
		if(sym[i] == c) n->data = (TokenSet)i;
	n->left = NULL;
	n->right = NULL;
	return n;
}
