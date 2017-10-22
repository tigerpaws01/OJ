#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define YES 2
#define NO 1
#define UNSET 0

char str[2005];
int isPalin[2005][2005];

bool isPalindrome(int l, int r)
{
	if(isPalin[l][r] != UNSET)
		return (isPalin[l][r] == YES ? true : false);
	else if(r - l > 2)
		isPalin[l][r] = (str[l] == str[r] && isPalindrome(l+1, r-1)) ? YES : NO;
	else
		isPalin[l][r] = str[l] == str[r] ? YES : NO;
	return (isPalin[l][r] == YES ? true : false);
}

int main()
{
	while(~scanf("%s", str))
	{
		// init
		int i, j, len = strlen(str);
		for(i = 0; i<len; i++)
			for(j = i+1; j<len ; j++)
				isPalin[i][j] = UNSET;
		// calc
		int sum = 0;
		for(i = 0; i<len; i++)
			for(j = i+1; j<len ; j++)
				if(isPalindrome(i, j)) sum++;
		printf("%d\n", sum);
	}
}
