#include <stdio.h>
#include <string.h>

int main()
{
	char a[20], b[10];
	int n, maxSum = 0;
	scanf("%s", a);
	scanf("%d", &n);
	while(n--)
	{
		int curSum = 0;
		scanf("%s", b);
		int aLen = strlen(a), bLen = strlen(b);
		int i, j;
		for(i = 0; i <= bLen-aLen; i++)
		{
			int result = 1;
			for(j = 0; j<aLen && result; j++)
				if(b[i+j] != a[j]) result = 0;
			if(result) curSum++;
		}
		maxSum = maxSum > curSum ? maxSum : curSum;
	}
	printf("%d", maxSum);
}
