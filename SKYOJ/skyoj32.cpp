// Best Cow Line
#include <cstdio>
#include <string.h>
#include <iostream>
using namespace std;

char str[505];

int main()
{
	while(cin >> str)
	{
		int length = strlen(str);
		int start = 0, end = length-1, output = 0;
		while(output < length)
		{
			if(str[start] < str[end])
			{
				cout << str[start++];
				output++;
			}
			else if(str[start] > str[end])
			{
				cout << str[end--];
				output++;
			}
			else
			{
				int os = start+1, oe = end-1;
				bool output_s = true;
				while(os < oe)
				{
					if(str[os] < str[oe])
					{
						break;
					}
					else if(str[oe] < str[os])
					{
						output_s = false;
						break;
					}
						
					os++, oe--;
				}
				
				if(output_s)cout << str[start++];
				else cout << str[end--];
				output++;
			}
		}
		cout << "\n";
	}
}
