#include <stdio.h>
#define MAX 10005
int drink[MAX]; // The final drinks u can get by buying n drinks

int main()
{
	// build table
	int i, N;
	for(i = 0; i<MAX; i++)
	{
		drink[i] = i;
		int d = i;
		for(;d>=3;d = (d/3) + (d%3))
			drink[i] += d/3;
	}
	// get input
	scanf("%d", &N);
	for(i = 0; i<MAX && drink[i] < N; i++);
	printf("%d\n", i);
}
