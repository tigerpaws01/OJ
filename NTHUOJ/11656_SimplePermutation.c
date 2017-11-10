#include <stdio.h>
#include "function.h"

void print(int level, int n)
{
	if(level == 1 && level == n)
	{
		printf("1\n");
		return;
	}
	
	printf("%d ", level);
	if(level != n) 
	{
		print(level+1, n);
		printf("%d%c", level, (level == 1 ? '\n' : ' '));
	}
}
