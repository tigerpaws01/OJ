#include <cstdio>
#include <iostream>
using namespace std;

int pos;
char str[100000];
bool input[26];

void getResult(int,int);
bool calculate();

// recursively determine the sequence of input
void getResult(int vars, int total)
{
	if(vars < total)
	{
		input[vars] = false;
		getResult(vars+1, total);
		
		input[vars] = true;
		getResult(vars+1, total);
	}
	else
	{
		pos = 0;
		bool r = calculate();
		/*printf("Sequence: ");
		for(int i = 0; i<total; i++)
		{
			printf("%d ", input[i] ? 1 : 0);
		}
		printf("Result: %d\n", r ? 1 : 0);*/
		if(r)
		{
			for(int i = 0; i<total; i++)
			{
				printf("%d ", input[i] ? 1 : 0);
			}
			printf("\n");
		}
	}
	
}

bool calculate()
{
	bool l, r;
	if(str[pos] == '&')
	{
		pos++;
		l = calculate();
		r = calculate();
		return l && r;
	}
	else if(str[pos] == '|')
	{
		pos++;
		l = calculate();
		r = calculate();
		return l || r;
	}
	else if(str[pos] == '^')
	{
		pos++;
		l = calculate();
		r = calculate();
		return l != r;
	}
	else
	{
		return input[ str[pos++]-'A' ];
	}
}

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	scanf("%s", str);
	getResult(0, a);
	return 0;
}
