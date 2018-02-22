#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1005

char a[MAX], b[MAX];

int Num(char *head, int index, int len)
{
	if(index >= len) return 0;
	return (head[index] - '0');
}

void Reverse(char *head, int len)
{
	int l = 0, r = len - 1;
	while(l < r)
	{
		char temp = head[l];
		head[l] = head[r];
		head[r] = temp;
		l++, r--;
	}
}

int main()
{
	
	while(~scanf("%s%s", a, b))
	{
		// digits of both nums
		int da = strlen(a), db = strlen(b);
		int digits = (da > db ? da : db), i;
		int result[MAX] = {0}, carries = 0;
		
		// reverse so that their lowest digits are aligned
		Reverse(a, da);
		Reverse(b, db);
		
		// Add
		for(i = 0; i < digits; i++)
		{
			result[i] = Num(a, i, da) + Num(b, i, db);
		}
		// Calculate carries
		for(i = 0; (i <= digits) || (i > digits && result[i] != 0); i++)
		{
			if(result[i] >= 10)
			{
				result[i+1] += result[i] / 10;
				result[i] %= 10;
				carries++;
			}
		}
		
		printf("%d\n", carries);
	}
}
