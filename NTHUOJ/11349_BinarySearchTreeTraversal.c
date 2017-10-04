#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void create_tree(Node **root, int n)
{
	int input;
	scanf("%d", &input);
	*root = (Node*) malloc(sizeof(Node));
	(*root)->data = input;
	(*root)->left = NULL;
	(*root)->right = NULL;
	n--;
	// get remaining nums input
	while(n--)
	{
		scanf("%d", &input);
		Node * cur = *root;
		while(1)
		{
			if(input < cur->data) // put it left
			{
				if(cur->left == NULL)
				{
					cur->left = (Node*) malloc(sizeof(Node));
					cur->left->data = input;
					cur->left->left = NULL;
					cur->left->right = NULL;
					break;
				}
				else
				{
					cur = cur->left;
				}
			}
			else if(input == cur->data)
			{
				break;
			}
			else // put it right
			{
				if(cur->right == NULL)
				{
					cur->right = (Node*) malloc(sizeof(Node));
					cur->right->data = input;
					cur->right->left = NULL;
					cur->right->right = NULL;
					break;
				}
				else
				{
					cur = cur->right;
				}
			}
		}
	}
	
}
void preorder(Node * root)
{
	if(root != NULL)
	{
		printf(" %d", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(Node * root)
{
	if(root != NULL)
	{
		
		inorder(root->left);
		printf(" %d", root->data);
		inorder(root->right);
	}
}

void postorder(Node * root)
{
	if(root != NULL)
	{
		
		postorder(root->left);
		postorder(root->right);
		printf(" %d", root->data);
	}
}

void print_tree(Node *root)
{
	printf("preorder:");
	preorder(root);
	printf("\n");
	
	printf("inorder:");
	inorder(root);
	printf("\n");
	
	printf("postorder:");
	postorder(root);
	printf("\n");
}
