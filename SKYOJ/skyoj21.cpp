#include <cstdio>
#include <iostream>
#define MAX 10000000
//#define DEBUG
using namespace std;

int n; // number of elements
int rock[MAX];

void push(int value)
{
	rock[n++] = value;
	int i = n-1;
	// keep comparing it with the parent node, til it is no larger than its children
	for(int p = i/2 - (i % 2 ? 0 : 1); p >= 0 && value <= rock[p]; i = p, p = i/2 - (i % 2 ? 0 : 1))
	{
		int temp = rock[i];
		rock[i] = rock[p];
		rock[p] = temp;
	}
}

void pop()
{
	if(n == 0)
	{
		printf("pop empty!\n");
		return;
	}
	rock[0] = rock[--n];
	// sink
	int i = 0, child;
	
	while(1)
	{
		if(2*i + 1 >= n) // no more children
			break;
		else if(2*i + 2 >= n) // only one children
			if(rock[2*i+1] < rock[i])
			{
				child = 2*i+1;
				int temp = rock[i];
				rock[i] = rock[child];
				rock[child] = temp;
				break;
			}
			else
				break;
		else // two children
		{
			if(rock[i] < rock[2*i+1] && rock[i] < rock[2*i+2])
				break;
			else 
			{
				child = (rock[2*i+1] < rock[2*i+2]) ? 2*i+1 : 2*i+2;
				int temp = rock[i];
				rock[i] = rock[child];
				rock[child] = temp;
				i = child;
			}
		}
		
	}
}

void top()
{
	if(n)
		printf("%d\n", rock[0]);
	else
		printf("top empty!\n");
}

void print()
{
	for(int i = 0; i<n; i++) printf("%d ", rock[i]);
	printf("\n");
}

int main()
{
	n = 0;
	int T, temp;
	char cmd[10];
	scanf("%d", &T);
	while(T--)
	{
		scanf("%s", cmd);
		if(cmd[0] == 'p' && cmd[1] == 'u') // push
		{
			scanf("%d", &temp);
			push(temp);
			#ifdef DEBUG
				print();
			#endif
		}
		else if(cmd[0] == 't') // top
		{
			top();
			#ifdef DEBUG
				print();
			#endif
		}
		else // pop
		{
			pop();
			#ifdef DEBUG
				print();
			#endif
		}
	}
	return 0;
}

