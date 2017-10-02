#include <cstdio>
#include <iostream>
using namespace std;

// sum of factor digit
int GetSFD(int n){

	int result = 0;
	for(int i = 1; i <= n/2; i++)
	{
		if(n % i == 0)
		{
			int c = i;
			while(c > 0)
			{
				result += c % 10;
				c /= 10;
			}
		}
	}
	int c = n;
	while(c > 0)
	{
		result += c % 10;
		c /= 10;
	}
	return result;
}

int SFD[3005], DDFlen[3005];

int main()
{
	for(int i = 1; i<3002; i++)
	{
		SFD[i] = GetSFD(i);
	}
	for(int i = 1; i<3002; i++)
	{
		int ddflen = 1, index = i;
		while(SFD[index] != index)
		{
			ddflen++;
			index = SFD[index];
		}
		
		DDFlen[i] = ddflen;
	}
	/*// TEST
	int a;
	while(cin >> a)
	{
		cout << "DDFLEN of " << a << " is: " << DDFlen[a] << endl;
	}*/
	// Find a num with greatest DDFlen
	int m, n;
	int times = 0;
	while(cin >> m >> n)
	{
		times++;
		int min =(m<n ? m:n), max = (m>n ? m:n);
		int  greatest = min, i = min;
		for(; i <= max; i++)
		{
			greatest = DDFlen[i] > DDFlen[greatest] ? i : greatest;
		}
		// print
		int index = greatest;
		cout << "Input" << times << ": " << m << " " << n << "\n";
		cout << "Output" << times << ":";
		while(SFD[index] != index)
		{
			cout << " " << index;
			index = SFD[index];
		}
		cout << " " << index << "\n";
	}
}
