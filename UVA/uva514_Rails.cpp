#include <cstdio>
#include <iostream>

int stack[1005], stackTop = 0, pushCount = 0, requested[1005], N;

bool hasElement()
{
	return stackTop != 0;
}

int top()
{
	return (stack[stackTop-1]);
}

int pop()
{
	//printf("POPPED: %d\n", stack[stackTop-1]);
	return stack[--stackTop];
}

int push()
{
	//printf("PUSHED: %d\n", pushCount+1);
	stack[stackTop++] = ++pushCount;
}

int main()
{
	while(~scanf("%d", &N))
	{
		if(N == 0) break;   // termination
		while(~scanf("%d", &requested[0]))
		{
			if(requested[0] == 0) break;
			for(int i = 1; i<N; i++) scanf("%d", &requested[i]);  // input
			// init
			stackTop = 0,pushCount = 0;
			// for every input: check everything inside requested
			bool result = true;
			for(int index = 0; index<N; index++)
			{
				if(hasElement() && requested[index] < top()) result = false; // No.
				while(requested[index] > pushCount) push();
				pop();
			}
			printf(result ? "Yes\n" : "No\n");
		}
		printf("\n");
	}
}
