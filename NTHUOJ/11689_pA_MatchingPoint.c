#include <stdio.h>
#include <string.h>

char str1[25], str2[25];
int len1, len2;

int match(int index1, int index2)
{
	if(index2 == len2) return 1;
	if(index1 == len1) return 0;
	
	if(str1[index1] == str2[index2])
		return (match(index1+1, index2+1) + match(index1+1, index2));
	else
		return match(index1+1, index2);
}

int main()
{
	while(scanf("%s%s", str1, str2) != EOF)
	{
		len1 = strlen(str1);
		len2 = strlen(str2);
		printf("%d\n", match(0, 0));
	}
	return 0;
}
