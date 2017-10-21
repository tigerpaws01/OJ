#include <stdio.h>
#include <stdbool.h>

int request[1000005];
bool visit[1000005];

int main()
{
	int n, m, i;
	
	scanf("%d%d", &n, &m);
	for(i = 0; i<n; i++) visit[i] = false;

	for(i = 0; i<m; i++) scanf("%d", &request[i]);
		
	for(i = m-1; i>=0; i--)
	{
		if(!visit[ request[i] ]) printf("%d\n", request[i]);
		visit[ request[i] ] = true;
	}
	for(i = 1; i<=n; i++) if(!visit[i]) printf("%d\n", i);
}
