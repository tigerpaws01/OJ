#include <cstdio>
#include <iostream>
using namespace std;
long long int H(long long int n)
{
	if(n<=0) return 0;
	long long int t = n;
	long long int res = 0;
	for(int i = 2;;)
	{
		res += (n - t/i) * (i-1);
		n = t/i;
		if(n == 0) break;
		i = t/n +1;
	}
	return res;
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);
	long long int T, N;
	cin >> T;
	while(T--)
	{
		cin >> N;
		cout << H(N) << "\n";
	}
	return 0;
}
