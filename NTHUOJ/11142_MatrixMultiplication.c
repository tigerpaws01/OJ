#include <stdio.h>

int main()
{
	int n, m, p;
	long long int A[105][105], B[105][105];
	while(~scanf("%d%d%d", &n, &m, &p))
	{
		int i, j;
		for(i = 0; i<n; i++)
			for(j = 0; j<m; j++)
				scanf("%lld", &A[i][j]);
				
		for(i = 0; i<m; i++)
			for(j = 0; j<p; j++)
				scanf("%lld", &B[i][j]);
				
		for(i = 0; i<n; i++)
		{
			for(j = 0; j<p; j++)
			{
				long long int sum = 0, k;
				for(k = 0; k<m; k++) sum += A[i][k] * B[k][j];
				printf("%lld", sum);
				if(j != p-1) printf(" ");
			}
			printf("\n");
		}
		printf("\n");
	}
}
