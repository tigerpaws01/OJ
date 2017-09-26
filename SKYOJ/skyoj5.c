#include <cstdio>
#include <iostream>
using namespace std;

bool b[20] = {};

void move_in(int);
void move_out(int);

void move_out(int n)
{
	if(!b[n]) return;
	if(n == 1 && b[1])
	{
		printf("Move ring 1 out\n");
		b[1] = false;
		return;
	}
	if( n == 2 && b[2])
	{
		move_in(1);
		printf("Move ring 2 out\n");
		b[2] = false;
	}
	move_in(n-1);
	for(int i = n-2; i >= 1; i--)
		move_out(i);
	if(!b[n]) return;
	printf("Move ring %d out\n", n);
	b[n] = false;
}

void move_in(int n)
{
	if(b[n]) return;
	if(n == 1 && !b[1])
	{
		printf("Move ring 1 in\n");
		b[1] = true;
		return;
	}
	if( n == 2 && !b[2])
	{
		move_in(1);
		printf("Move ring 2 in\n");
		b[2] = true;
	}
	move_in(n-1);
	for(int i = n-2; i >= 1; i--)
		move_out(i);
	if(b[n]) return;
	printf("Move ring %d in\n", n);
	b[n] = true;
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i =1; i <= n; i++)
		b[i] = true;
	for(int i = n; i >= 0; i--)
		move_out(i);
}
