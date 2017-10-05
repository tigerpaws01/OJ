#include <stdio.h>
#define MAX 1000000
#define true 1
#define false 0

int prime[100000];
int isPrime[MAX]; // true = !prime, false = prime

int main()
{
	// build prime table
	int primeIndex = 0, i;
	isPrime[1] = true;
	for(i = 2; i<=MAX; i++)
		if(!isPrime[i])
		{
			prime[primeIndex++] = i;
			for(int j = 2*i; j<=MAX; j += i)
				isPrime[j] = true;
		}
	// get input
	int T, x, n;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d %d", &x, &n);
		// n-th smallest prime >= x
		int indicator = 0;
		for(i = 0; i<primeIndex && indicator < n; i++)
		{
			if(prime[i] >= x) indicator++;
		}
		printf("%d\n", prime[i-1]);
	}
}
