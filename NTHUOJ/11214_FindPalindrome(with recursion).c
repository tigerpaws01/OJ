#include <stdio.h>
#include <string.h>
#define UNKNOWN 0
#define YES 1
#define NO 2

int dp[1001][1001];
char str[1005];

int isPalindrome(int l, int r)
{
	if(dp[l][r] != UNKNOWN) return dp[l][r];
	
	if(r - l <= 2)
		dp[l][r] = (str[l] == str[r] ? YES : NO);
	else
		dp[l][r] = (str[l] == str[r] && isPalindrome(l+1, r-1)) ? YES : NO;
	
	return dp[l][r];
}

int main()
{
	int N;
	
	
	scanf("%d", &N);
	while(N--)
	{
		scanf("%s", str);
		int l, r, len = strlen(str), found = 0;
		
		// initialization
		for(l = 0; l < len && !found; l++)
			for(r = l + 2; r < len && !found; r++)
				dp[l][r] = UNKNOWN;
		
		for(l = 0; l < len && !found; l++)
			for(r = l + 2; r < len && !found; r++)
				if(isPalindrome(l, r) == YES) found = 1; // for every substring str[l, r]
		
		if(found) printf("Yes\n");
		else printf("No\n");
	}
}
