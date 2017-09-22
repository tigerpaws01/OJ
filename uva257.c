
// CODE髒成這樣不要看啦QQ 
#include <cstdio>
#include <string.h>

char str[5000];
char record[500][500];
int recordIndex = 0;

bool isPalin(int s, int e, int len)
{
	//printf("check from %d to %d, ", s, e);
	bool result = true;
	if(e >= len) return false;
	while(s < e)
	{
		result = result && (str[s] == str[e]);
		s++, e--;
	}
	//printf("result : %s", result ? "YES\n" : "NO\n");
	return result;
}

int main()
{
	while(~scanf("%s", str))
	{
		// check for palinword
		int pwCount = 0, maxlength = strlen(str);
		recordIndex = 0;
		for(int start = 0; start < maxlength-2 && pwCount < 2; start++)
		{
			//if(isPalin(start, start+2, maxlength) || isPalin(start, start+3, maxlength)) pwCount++;
			//pwCount += isPalin(start, start+2, maxlength) + isPalin(start, start+3, maxlength);
			bool test = false;
			// build up two char[]
			//
			char little[4], big[5];
			for(int i = 0; i <= 3; i++)
			{
				big[i] = str[start+i];
				if(i==3) continue;
				little[i] = str[start+i];
			}
			little[3] = '\0';
			big[4] = '\0';
			if(isPalin(start, start+3, maxlength) && isPalin(start, start+2, maxlength))
			{
				// four same character
				//printf("four same\n");
				test = true;
				bool test2 = true;
				// included ?
				for(int i = 0; i < recordIndex; i++)
				{
					
					if((strcmp(big, record[i]) == 0))
					{
						//printf("Found a same: %s\n",big);
						//test = true;
						test = false;
						
					}
					else
					{
						//printf("Found a new: %s\n",big);
						
						//pwCount++;
					}
				}
				for(int i = 0; i < recordIndex; i++)
				{
					
					 if((strcmp(little, record[i]) == 0))
					{
						//printf("Found a same: %s\n",little);
						test2 = false;
						
					}
					else
					{
						
						//printf("Found a new: %s\n",little);
						
					}
				}
				if(test || test2)
				{
					//printf("Found a new: %s\n",little);
					if(test) strcpy(record[recordIndex++], big);
					if(test2) strcpy(record[recordIndex++], little);
					pwCount++;
				}
			}
			else if(isPalin(start, start+3, maxlength))
			{
				test = true;
				// included ?
				for(int i = 0; i < recordIndex; i++)
				{
					
					if((strcmp(big, record[i]) == 0))
					{
						//printf("Found a same: %s\n",big);
						//test = true;
						test = false;
						
					}
					else
					{
						//printf("Found a new: %s\n",big);
						
						//pwCount++;
					}
				}
				if(test)
				{
					//printf("Found a new: %s\n",little);
					strcpy(record[recordIndex++], big);
					pwCount++;
				}
				//if(!test) pwCount++;
			}
			else if(isPalin(start, start+2, maxlength))
			{
				test = true;
				// included ?
				for(int i = 0; i < recordIndex; i++)
				{
					
					 if((strcmp(little, record[i]) == 0))
					{
						//printf("Found a same: %s\n",little);
						test = false;
						
					}
					else
					{
						
						//printf("Found a new: %s\n",little);
						
					}
				}
				if(test)
				{
					//printf("Found a new: %s\n",little);
					strcpy(record[recordIndex++], little);
					pwCount++;
				}
			}
			
		}
		if(pwCount >= 2) printf("%s\n", str);
	}
	return 0;
}
