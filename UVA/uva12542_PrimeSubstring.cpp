#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stack>
#define MAX 100005

using namespace std;

bool notPrime[MAX]; // true means not a prime
int prime[10000];
char primeSet[10000][15];
int main()
{
	//cin.tie(0);
	//ios::sync_with_stdio(false);
	// build prime table
	int primeIndex = 0;
	for(int i = 2; i <= 100000; i++)
	{
		if(notPrime[i] == false)
		{
			prime[primeIndex++] = i;
			for(int j=2*i; j<=100000; j+=i)
				notPrime[j] = true;
		}
	}
	
	// set prime num str
	for(int i = 0; i < primeIndex; i++)
	{
		stack<int> stk;
		int t = prime[i];
		while(t > 0)
		{
			stk.push(t%10);
			t/=10;
		}
		
		char * c = primeSet[i];
		while(!stk.empty())
		{
			*c = stk.top() + '0';
			stk.pop();
			c++;
		}
		*c = '\0';
		
	}
	char str[300];
	while(cin >> str)
	{
		if(strlen(str) == 1 && str[0] == '0') break;
		int largest = 0;
		for(int i = 0; i<primeIndex; i++)
			if(strstr(str, primeSet[i]) != NULL) largest = i;
		cout << prime[largest] << "\n";
	}
}
