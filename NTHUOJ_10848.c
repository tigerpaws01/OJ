#include "function.h"

int d1[4] = {1, 0, -1, 0};
int d2[4] = {0, 1, 0, -1};
int queueR[250000], queueC[250000];
int popIndex, pushIndex;



void flooding(int R, int C, int pr, int pc)
{
	// init
	popIndex = 0;
	pushIndex = 0;
	// push start
	queueR[pushIndex] = pr;
	queueC[pushIndex] = pc;
	pushIndex++;
	
	while(popIndex < pushIndex)
	{
		// Get top
		pr = queueR[popIndex];
		pc = queueC[popIndex];
		// Set water
		Map[pr][pc] = 'W';
		// push points around queue[popIndex]
		for(int i = 0; i < 4; i++)
		{
			int newpr = pr + d1[i], newpc = pc+d2[i];
			if(newpr >= 0 && newpc >= 0 &&
				 newpr < R && newpc < C &&
				 Map[newpr][newpc] == 'H')
			{
				// push this point
				queueR[pushIndex] = newpr;
				queueC[pushIndex] = newpc;
				pushIndex++;
			}
		}
		// pop
		popIndex++;
	}
}
