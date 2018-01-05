#include <stdio.h>
#include <stdbool.h>
#define MAX_NODES 1001

// A bad alternative to deal with graphs in C without better DSs...
typedef enum { BLACK, WHITE, UNKNOWN } Status;

typedef struct node
{
	bool visited;
	Status _status;
	int path[MAX_NODES] = {0}, paths = 0;

} Node;

// Nodes are numbered from 1 to N
Node graph[MAX_NODES];
int stack[MAX_NODES * MAX_NODES * 2], index = 0;

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int N, M;
		int i;
		int flag = 1;
		scanf("%d%d", &N, &M);

		// Initialization
		index = 0;
		for(i = 1; i <= N; i++)
		{
			graph[i].visited = false;
			graph[i]._status = UNKNOWN;
			graph[i].paths = 0;
		}

		// Get paths
		for(int i = 0; i < M; i++)
		{
			// No checking is needed since we've been assured of no multiple edges.
			int u, v;
			scanf("%d%d", &u, &v);
			graph[u].path[ graph[u].paths++ ] = v;
			graph[v].path[ graph[v].paths++ ] = u;
		}

		// Push the first node into stack
		stack[index++] = 1;
		graph[1]._status = BLACK;

		while(index > 0 && flag)
		{
			// Pop
			int current = stack[--index];
			// Skip if visited
			if(graph[current].visited) continue;

			graph[current].visited = true;
			// For every node it connects to, dye a difference color
			// then push them into the stack
			Status new_status = graph[current]._status == BLACK ? WHITE : BLACK;
			for(i = 0; i < graph[current].paths; i++)
			{
				if(graph[ graph[current].path[i] ]._status == UNKNOWN)
					graph[ graph[current].path[i] ]._status = new_status;
				else if(graph[ graph[current].path[i] ]._status != new_status)
					flag = 0;

				stack[index++] = graph[current].path[i];
			}

		}

		printf("%s\n", (flag ? "Yes" : "No"));
	}
}
