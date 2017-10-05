#include <stdio.h>

int main()
{
	int T, n, m, t;
	scanf("%d", &T);
	while(T--)
	{
		int i;
		scanf("%d%d%d", &n, &m, &t);
		for(i = 0; i<(t-m) && i<n; i++)
			printf("-");
		for(; i<n && i<t; i++)
			printf("^");
		for(; i<n; i++)
			printf("-");
		printf("\n");
	}
}
