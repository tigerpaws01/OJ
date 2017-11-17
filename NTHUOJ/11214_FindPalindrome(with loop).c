#include <stdio.h>
#include <string.h>

int main()
{
	int N;
	char str[1005];
	
	scanf("%d", &N);
	while(N--)
	{
		scanf("%s", str);
		int l, r, len = strlen(str), found = 0;
		
		for(l = 0; l < len && !found; l++)
		{
			for(r = l + 2; r < len && !found; r++)
			{
				// for every substring str[l, r]
				int leftBorder = l, rightBorder = r, result = 1;
				while(leftBorder < rightBorder && result)
				{
					if(str[leftBorder] != str[rightBorder]) result = 0;
					leftBorder++, rightBorder--;
				}
				
				if(result) found = 1;
			}
		}
		
		if(found) printf("Yes\n");
		else printf("No\n");
	}
}
