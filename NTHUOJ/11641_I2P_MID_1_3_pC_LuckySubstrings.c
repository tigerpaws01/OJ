#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int ninePosition[200005], nines = 0;
char str[200005];

int main()
{
	while(~scanf("%s", str))
	{
		int len = strlen(str);
		int i;
		long long int luckySubstrings = 0;
		
		// init
		nines = 0;
		
		// Find out every position of 9
		for(i = 0; i < len; i++)
			if(str[i] == '9')
				ninePosition[nines++] = i;
		
		// For every nine...
		for(i = 0; i < nines; i++)
		{
			if(i != nines - 1)
				luckySubstrings += (ninePosition[i] + 1) * (ninePosition[i + 1] - ninePosition[i]);
			else // last nine
				luckySubstrings += (ninePosition[i] + 1) * (len - ninePosition[i]);
		}
		
		// Output
		printf("%lld\n", luckySubstrings);
	}
}
