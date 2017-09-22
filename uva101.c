#include <iostream>
#include <cstdio>
#include <stdlib.h>
#define max 30
using namespace std;

void returnAbove(int);
void stackOn(int, int);
int stack[max][max] = {};
int pos_x[max] = {}, top[max] = {};

/*
void returnAbove(int num)
{
	// 先找到num方塊的位置，從y+1開始逐個回復
	int y, block;
	for(y = 0;stack[pos_x[num]][y] != num; y++){
	}
	y++;
	while(y <= top[pos_x[num]])
	{
		// 返回[posnum][y]處的方塊至 [ stack[posnum][y] ][0]
		block = stack[pos_x[num]][y];
		stack[block][0] = block;
		pos_x[block] = block;
		stack[pos_x[num]][y] = stack[pos_x[num]][y+1];
		top[pos_x[num]]--;
		top[block]++;
	}


}*/

void returnAbove(int num)
{
	// 從num該列的TOP開始，逐個向下回復
	int block;
	while(stack[pos_x[num]][top[pos_x[num]]] != num)
	{
		block = stack[pos_x[num]][ top[pos_x[num]]-- ];
		stack[block][++top[block]] = block;
		pos_x[block] = block;
	}
}

void stackOn(int from, int to)
{
	int temp[max] = {}, x = pos_x[from], X = pos_x[to], index = 0;
	// 將from那一列，從上到下存入temp，並且也存入from
	while(stack[x][top[x]] != from)
	{
		temp[index++] = stack[x][top[x]--];
	}
	// 存入from
	temp[index] = stack[x][top[x]--];
	// 把temp疊在to的那一列上：從top+1開始
	while(index >= 0)
	{
		pos_x[temp[index]] = X;
		stack[X][++top[X]] = temp[index--];

	}

}

int main()
{
	char c1[255], c2[255];
	int v1, v2, n;
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 0; i < n ; ++i) // init
		{
			stack[i][0] = i;
			pos_x[i] = i;
			top[i] = 0;
		}
		while(scanf("%s", c1) != EOF)
		{
			if(c1[0] == 'q') break;
			scanf("%d%s%d", &v1, c2, &v2);
			//cin >> v1 >> c2 >> v2;
			if(v1 == v2 || pos_x[v1] == pos_x[v2]) continue;

			// start
			if(c1[0] == 'm')
			{
				if(c2[3] == 'o') // move onto
				{
					returnAbove(v1);
					returnAbove(v2);
					stackOn(v1, v2);
				}
				else // move over
				{
					returnAbove(v1);
					stackOn(v1, v2);
				}
			}
			else
			{
				if(c2[3] == 'o') // pile onto
				{
					returnAbove(v2);
					stackOn(v1, v2);
				}
				else // pile over
				{
					stackOn(v1, v2);
				}
			}
		}
		// printf
		for(int i =0; i<n; i++)
		{
			printf("%d:", i);
			for(int j = 0;j <= top[i];j++)
			{
				printf(" %d", stack[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
