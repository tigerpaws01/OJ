#include <stdio.h>
#include <math.h>

int bits[25] = {0};

int main()
{
	int n, input, i, bitIndex = 0;
	long long int sum = 0;
	scanf("%d", &n);

	// process every input
	for(i = 0; i < n; i++, bitIndex = 0)
	{
		scanf("%d", &input);
		while(input > 0)
		{
			bits[bitIndex++] += (input % 2);
			input >>= 1;
		}

	}
	
	// wisely choose every bit of k while adding them together
	for(int i = 0; i < 25; i++)
	{
		bits[i] = (n - bits[i] < bits[i] ? n - bits[i] : bits[i]);
		sum += pow(2, i) * bits[i];
	}

	printf("%lld\n", sum);

}
