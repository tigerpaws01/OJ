#include <stdio.h>
typedef long long int ll;

ll me(ll base, ll exp, ll mod)
{
	ll result = 1;
	while(exp > 0)
	{
		if(exp % 2 == 1)
			result = (result * base) % mod;
		exp /= 2;
		base = (base * base) % mod;
	}
	return result;
}


int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		ll A, N, M;
		scanf("%lld%lld%lld", &A, &N, &M);
		printf("%lld\n", me(A, N, M));
	}

}
