#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
	int _a = *(int*)a,
			_b = *(int*)b;
	return _a > _b;
}

int main()
{
	int n, array[100000], k, T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		for(k = 0; k<n; k++) scanf("%d", &array[k]);
		qsort(array, n, sizeof(int), cmp);
		for(k = 0; k<n; k++) 
		{
			printf("%d", array[k]);
			if(k != n-1) printf(" ");
			else printf("\n");
		}
	}
	
}
