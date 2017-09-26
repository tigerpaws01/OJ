#include <cstdio>
#include <iostream>
#include<stdlib.h>
#include <queue>
#define MAX 1005
using namespace std;

struct point{
	int x, y;
};

int N, M, aux, auy;
char maze[MAX][MAX];
int lastStep[MAX][MAX];
queue<point*> q;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, step[4] = {1, 0, 3, 2};

void push(int y, int x)
{
	point* p = (point*)malloc(sizeof(point));
	p->x = x;
	p->y = y;
	q.push(p);
}

point* front()
{
	return q.front();
}

void printPath(int y, int x, int length = 1)
{
	if(lastStep[y][x] == -2)
	{
		printf("%d\n(%d,%d)\n", length, y, x);
		return;
	}
	printPath(y + dir[ lastStep[y][x] ][0], x + dir[ lastStep[y][x] ][1], length+1);
	printf("(%d,%d)\n", y, x);
}

int main()
{
	scanf("%d%d", &N, &M);
	bool found = false, mouseFound = false;
	for(int i = 0; i<N; i++)
	{
		scanf("%s", maze[i]);
		for(int j = 0; j<M && !found; j++)
			if(maze[i][j] == '&')
			{
				aux = j; auy = i;
				found = true;
			}
	}
	// init
	for(int i = 0; i<N; i++)
	for(int j = 0; j<M; j++)
		lastStep[i][j] = -1;
	// do BFS from (auy, aux)
	push(auy, aux);
	lastStep[auy][aux] = -2;
	while(q.front() != NULL && ! mouseFound)
	{
		// pop a point
		point* cur = front();
		// explore
		for(int i = 0; i <4; i++)
		{
			int newx = cur->x + dir[i][1], newy = cur->y + dir[i][0];
			// continue if visited or out of border
			if((lastStep[newy][newx] != -1) + (newy < 0) + (newy >= N) + (newx < 0) + (newx >= M) > 0) continue;
			
			// for a path: push into the queue
			else if(maze[newy][newx] == '.')
			{
				lastStep[newy][newx] = step[i];
				push(newy, newx);
			}
			// for the mouse, output the result
			else if(maze[newy][newx] == '@')
			{
				lastStep[newy][newx] = step[i];
				mouseFound = true;
				printPath(newy, newx);
				break;
			}
		}
		q.pop();
	}
}
