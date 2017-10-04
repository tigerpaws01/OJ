#include <stdio.h>
#include <stdlib.h>
#include "function.h"


void printInfix(Node *root)
{
	if(!root == NULL)
	{
		printInfix(root->left);
		printf("%c", root->data);
		if(root->right != NULL && root->right->left != NULL)
		{
			printf("(");
			printInfix(root->right);
			printf(")");
		}
		else
		{
			printInfix(root->right);
		}
		
	}
}
