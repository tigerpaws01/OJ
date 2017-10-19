#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include <iostream>

// You need to implement these functions
Node* new_node(int key);
void insert(Node **root, int key);
void deleteNode(Node **root, int key);
int numOf(Node **root, int key);
void actualDeletion(Node **root, int key);
int deleteSmallest(Node **root);
int deleteGreatest(Node **root);

Node* new_node(int key)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = key;
    node->left = node->right = NULL;

    return node;
}

void insert(Node **root, int key)
{
	if(*root == NULL)
	{
		*root = new_node(key);
		return;
	}
	Node *last = *root, *cur = *root;
	for(;cur != NULL;
		last = cur, cur = (cur->data > key ? cur->left : cur->right));

	if(last->data > key) last->left = new_node(key);
	else last->right = new_node(key);

}

int numOf(Node **root, int key)
{
	if(*root == NULL) return 0;
	return numOf(&((*root)->left), key) + ((*root)->data == key ? 1 : 0) + numOf(&((*root)->right), key);
}

// make sure root has a right subtree
int deleteSmallest(Node **root)
{
	Node *last, *cur;
	if((*root)->right == NULL) return 0;
	last = *root, cur = (*root)->right;
	
	if(cur->left == NULL)
	{
		last->right = cur->right;
		int toRt = cur->data;
		free(cur);
		return toRt;
	}
	else
	{
		for(;cur->left != NULL;last = cur, cur = cur->left);
		last->left = cur->right;
		int toRt = cur->data;
		free(cur);
		return toRt;
	}
	
	
}

int deleteGreatest(Node **root)
{
	Node *last, *cur;
	if((*root)->left == NULL) return 0;
	last = *root, cur = (*root)->left;

	if(cur->right == NULL)
	{
		last->left = cur->left;
		int toRt = cur->data;
		free(cur);
		return toRt;
	}
	else
	{
		for(;cur->right != NULL;last = cur, cur = cur->right);
		last->right = cur->left;
		int toRt = cur->data;
		free(cur);
		return toRt;
	}
}

void actualDeletion(Node **root, int key)
{
	// No nodes
	if(*root == NULL) return;
	Node *last, *cur = *root;
	
	// Only the root
	if(cur->left == NULL && cur->right == NULL)
	{
		if(cur->data == key) free(*root), *root = NULL;
		return;
	}
	
	// Delete the root
	if(cur->data == key)
	{
		cur->data = (cur->left != NULL ? deleteGreatest(root) : deleteSmallest(root));
		return;
	}
	
	// Other situations
	last = *root,
	cur = (key > (*root)->data ? (*root)->right : (*root)->left);
	for(;cur != NULL && cur->data != key;
		last = cur, cur = key > cur->data ? cur->right : cur->left);
		
	if(cur == NULL) return;
	
	if(cur->left == NULL && cur->right == NULL)
	{
		if(last->left == cur) last->left = NULL;
		else last->right = NULL;
		free(cur);
	}
	else if(cur->left == NULL || cur->right == NULL)
	{
		if(last->left == cur) last->left = (cur->left != NULL ? cur->left : cur->right);
		else last->right = (cur->left != NULL ? cur->left : cur->right);
		free(cur);
	}
	else
	{
		cur->data = deleteGreatest(&cur);
	}
}

void deleteNode(Node **root, int key)
{
	int N = numOf(root, key);
	while(N--) actualDeletion(root, key);
}
