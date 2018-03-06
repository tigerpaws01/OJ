// Simulating queue with array
#include <stdio.h>
#include <stdbool.h>
#define MAX 505
#define INF 1e8
#define min(a,b) (a < b ? a : b);

struct point
{
	int x, y;
};

char map[MAX][MAX];
bool visit[MAX][MAX];
int leastStep[MAX][MAX];
int qh, qt;

struct point q[MAX * MAX + 50], fin;

bool Empty()
{
	return (qh == qt);
}

void Push(int y, int x)
{
	if(Empty()) qh = qt = 0;
	q[qh].y = y;
	q[qh++].x = x;
}



void Pop()
{
	qt++;
	if(Empty()) qh = qt = 0;
}

bool FinalReached()
{
	return (leastStep[fin.y][fin.x] != INF);
}


int main()
{
	int N, R, C;
	scanf("%d", &N);

	while(N--)
	{
		scanf("%d%d", &R, &C);
		int i, j;

		// initialization
		qh = qt = 0;
		for(i = 0; i < R; i++)
			for(j = 0; j < C; j++)
				visit[i][j] = false, leastStep[i][j] = INF;

		// input
		for(i = 0; i < R; i++)
			for(j = 0; j < C; j++)
			{
				char input;
				scanf(" %c", &input);
				map[i][j] = input;

				// Record the final point
				if(input == 'F') fin.y = i, fin.x = j;

				// Push the start point into queue
				if(input == 'S')
				{
					leastStep[i][j] = 0;
					Push(i, j);
					visit[i][j] = true;
				}

			}

		// BFS
		while(!Empty() && !FinalReached())
		{
			struct point cur = q[qt];
			int curStep = leastStep[cur.y][cur.x];
			Pop();

			// for the four points around 'cur'...
			int yp[4] = {1, -1, 0, 0}, xp[4] = {0, 0, 1, -1};
			for(i = 0; i < 4; i++)
			{
				int newy = cur.y + yp[i], newx = cur.x + xp[i];

				// Skip illegal points: out of range, or walls
				if((newy < 0 || newx < 0 || newy >= R || newx >= C) || map[newy][newx] == '#') continue;

				// Record the leastStep of it
				// Relaxation at the same time (actually not needed here as it is BFS)
				leastStep[newy][newx] = min(leastStep[newy][newx], curStep + 1);
				// Push them into queue if not visited yet
				if(!visit[newy][newx])
				{
					Push(newy, newx);
					// mark as visited
					visit[newy][newx] = true;
				}
			}
		}


		// get the result
		if(!FinalReached()) printf("-1\n");
		else printf("%d\n", leastStep[fin.y][fin.x]);
	}
}
