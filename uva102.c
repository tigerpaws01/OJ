#include <iostream>
#include <cstdio>

int b[3], g[3], c[3];

int calculation(int bIgn, int gIgn, int cIgn)
{
	int result = 0;
	for(int i = 0; i < 3; i++)
	{
		result += b[i] * (i == bIgn ? 0 : 1) +
		 					g[i] * (i == gIgn ? 0 : 1) +
							c[i] * (i == cIgn ? 0 : 1);
	}
	return result;
}


int main()
{
	while(~scanf("%d%d%d%d%d%d%d%d%d", &b[0], &g[0], &c[0], &b[1], &g[1], &c[1], &b[2], &g[2], &c[2]))
	{
		// 頂多六種可能
		// BCG, BGC, CBG, CGB, GBC, GCB
		// BCG
		char order[6][4] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};
		int Ign[6][3] = { {0,2,1}, {0,1,2}, {1,2,0}, {2,1,0}, {1,0,2}, {2,0,1}
		};
		int index = 5, min = 1e9, minIndex = 0;
		for(;index >= 0;index--)
		{
			int calc = calculation(Ign[index][0], Ign[index][1], Ign[index][2]);
			//printf("By order of, %s,  %d\n", order[index], calc);
			if(min >= calc)
			{
				
				minIndex = index;
				min = calc;
			}
		}
		printf("%s %d\n", order[minIndex], min);
	}
}
