// 一維kd樹
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <stack>
//#define DEBUG
using namespace std;

struct Node{
	int d;
	Node *l, *r;
};

Node *NewNode(int value)
{
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->d = value;
	newnode->l = NULL;
	newnode->r = NULL;
	return newnode;
}

void Insert(Node ** root, int value)
{
	if(*root == NULL)
	{
		*root = NewNode(value);
		return;
	}
	
	Node *last = *root, *cur = *root;
	for(;cur != NULL;
		last = cur, cur = (cur->d > value ? cur->l : cur->r));

	if(value > last->d)	last->r = NewNode(value);
	else if(value < last->d) last->l = NewNode(value);
}

int FindMax(Node *root)
{
	// Assuming root is never NULL
	while(root->r != NULL) root = root->r;
	return root->d;
}

bool Delete(Node *& root, int value)
{
	if(root == NULL) return false;
	if(root->d == value)
	{
		if(root->l == NULL || root->r == NULL)
		{
			Node *toD = root;
			root = root->l != NULL ? root->l : root->r;
			free(toD);
			return true;
		}
		root->d = FindMax(root->l);
		return Delete(root->l, root->d);
	}
	return Delete(root->d > value ? root->l : root->r, value);
}

int Abs(int a)
{
	return a > 0 ? a : -a;
}

void Query(Node *root, int value)
{
	stack<int> result;

	Node *cur = root;

	for(;cur != NULL; cur = (cur->d > value ? cur->l : cur->r))
	{
		#ifdef DEBUG
			cout << "  Travelling " <<  cur->d << '\n';
		#endif
 		if(result.empty())
		{
			#ifdef DEBUG
				cout << "   Pushed " << cur->d << '\n';
			#endif
			result.push(cur->d);
			continue;
		}

		int curD = Abs(cur->d - value), tD = Abs(result.top() - value);
		if(curD > tD) continue;
		for(; curD < tD; tD = result.empty() ? -1 : Abs(result.top() - value))
		{
			#ifdef DEBUG
				cout << "   Popped " << result.top() << '\n';
			#endif
			result.pop();
		}
		#ifdef DEBUG
			cout << "   Pushed " << cur->d << '\n';
		#endif
		result.push(cur->d);
	}
	#ifdef DEBUG
		cout << "   Stack has " << result.size() << " Elements.\n";
	#endif
	if(result.size() == 1)
		cout << result.top() << '\n';
	else
	{
		int a = result.top();
		result.pop();
		int b = result.top();
		cout << (a < b ? a : b) << " " << (a > b ? a : b) << '\n';
	}

}

void Clean(Node *&root)
{
	if(root == NULL) return;
	Clean(root->l);
	Clean(root->r);
	free(root);
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);
	Node *root = NULL;
	char cmd[10];
	int temp, T;
	cin >> T;
	while(T--)
	{
		cin >> cmd >> temp;
		if(cmd[0] == 'i')
		{
			Insert(&root, temp);
			#ifdef DEBUG
				InorderPrint(root);
				cout << '\n';
			#endif
		}
		else if(cmd[0] == 'd')
		{
			bool b = Delete(root, temp);
			#ifdef DEBUG
				cout << ">> Deletion " << (b ? "Successful.\n" : "Failed\n");
				InorderPrint(root);
				cout << '\n';
			#endif
		}
		else Query(root, temp);
	}
	Clean(root);
	return 0;
}
