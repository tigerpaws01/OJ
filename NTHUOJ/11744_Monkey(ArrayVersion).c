#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200001

char str[MAX], right[MAX];

void Print(int s_len, int r_len)
{
	int i;
	str[s_len] = '\0';
	printf("%s", str);
	for(i = r_len-1; i >= 0; --i) printf("%c", right[i]);
	printf("\n");
}

int main(){
	char c;
	int i_s = 0, i_r = 0;
	
	while(~scanf(" %c", &c))
	{
		
		if(c == '>')
		{
			if(i_r > 0) str[i_s++] = right[--i_r];
		}
		else if(c == '<')
		{
			if(i_s > 0) right[i_r++] = str[--i_s];
		}
		else if(c == 'D')
		{
			if(i_r > 0) i_r--;
		}
		else
			str[i_s++] = c;
	}
	
	Print(i_s, i_r);
	return 0;
}
