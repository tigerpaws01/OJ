#include <stdio.h>
#include <iostream>
typedef long long int ll;
using namespace std;

ll me(ll base, ll exp, ll mod)
{
	ll result = 1;
	while(exp > 0)
	{
		if(exp % 2 == 1)
			result = (result * base) % mod;
		exp /= 2;
		base = (base*base) % mod;
	}
	return result;
}


int main()
{
	ll B, P, M;
	while(cin >> B >> P >> M)
		cout << me(B, P, M) << "\n";
}
