#include <cstdio>
#include <iostream>
using namespace std;

int gcd(int a, int b)
{
	if(b == 0) return a;
	return gcd(b, a%b);
}

int result[505][505];

int main()
{
	for(int i = 1; i<501; i++)
	for(int j = i+1; j<=501; j++)
	{
		result[i][j] = gcd(i, j);
	}
	
	int N;
	while(cin >> N)
	{
		if(N == 0) break;
		int G = 0;
		for(int i = 1; i<N; i++)
		for(int j = i+1; j<=N; j++)
			G += result[i][j];
		cout << G << "\n";
	}
	return 0;
}
