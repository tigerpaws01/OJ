#include <stdio.h>
#include <stdlib.h>
#include "function.h"

// You need to implement these functions
void insert(Node **root, int key)
{
	if(*root == NULL)
	{
		*root = (Node*)malloc(sizeof(Node));
		(*root)->data = key;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return;
	}
	Node *cur = *root;
	while(1)
	{
		if(key <= cur->data && cur->left == NULL)
		{
			cur->left = (Node*)malloc(sizeof(Node));
			cur->left->data = key;
			cur->left->left = NULL;
			cur->left->right = NULL;
			break;
		}
		else if(key > cur->data && cur->right == NULL)
		{
			cur->right = (Node*)malloc(sizeof(Node));
			cur->right->data = key;
			cur->right->left = NULL;
			cur->right->right = NULL;
			
			break;
		}
		else if(key <= cur->data)
			cur = cur->left;
		else if(key > cur->data)
			cur = cur->right;
	}
}

int deleteSmallest(Node *root)
{
	Node * cur, *last = root;
	last = root;
	cur = root->right;
	if(cur->left == NULL)
	{
		last->right = cur->right;
		int result = cur->data;
		free(cur);
		return result;
	}
	else
	{
		for(;cur->left != NULL;)
		{
			last = cur;
			cur = cur->left;
		}
		last->left = cur->right;
		int result = cur->data;
		free(cur);
		return result;
	}
	
	
}

int deleteGreatest(Node *root)
{
	Node * cur, *last = root;
	cur = root->left;
	if(cur->right == NULL)
	{
		last->left = cur->left;
		int result = cur->data;
		free(cur);
		return result;
	}
	else{
	 for(;cur->right != NULL;)
		{
			last = cur;
			cur = cur->right;
		}
		last->right = cur->left;
		int result = cur->data;
		free(cur);
		return result;
	}
	
}

int numOf(Node *root, int key)
{
	if(root == NULL) return 0;
	return numOf(root->left, key) + (root->data == key ? 1 : 0) +numOf(root->right, key);
}

void actualDeletion(Node **root, int key)
{
	if(*root == NULL) return;
	if((*root)->left == NULL && (*root)->right == NULL)
	{
		if((*root)->data == key) {
			Node *toD = *root;
			*root = NULL;
			free(toD);
			return;
		}
		else return;

	}
	// if it is the root to be deleted
	if((*root)->data == key)
	{
		(*root)->data = ((*root)->right != NULL ? deleteSmallest(*root) : deleteGreatest(*root));
		return;
	}
	// else
	Node * last = *root,
	*cur = (*root)->data > key ? (*root)->left : (*root)->right;
	for(;cur != NULL && cur->data != key;
		last = cur, cur = cur->data > key ? cur->left : cur->right)
		{
			//printf("NOW ON:%d\n", cur->data);
			//system("pause");
		}
	if(cur == NULL) return;
	//printf("KEY:%d\n", key);
	if(cur->left == NULL && cur->right == NULL)
	{
		if(last->left == cur) last->left = NULL;
		else last->right = NULL;
		free(cur);
		return;
	}
	else if(cur->left == NULL || cur->right == NULL)
	{
		if(last->left == cur) last->left = (cur->left == NULL ? cur->right : cur->left);
		else last->right = (cur->left == NULL ? cur->right : cur->left);
		free(cur);
		return;
	}
	else
	{
		cur->data = deleteGreatest(cur);
		return;
	}
}

void deleteNode(Node **root, int key)
{
	int k = numOf(*root, key);
	while(k--) actualDeletion(root, key);
	
}
