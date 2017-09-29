#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <stack>
using namespace std;

int N;
long long int height[100005];
stack<int> s;

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	while(cin >> N)
	{
		long long int biggest = 0;
		N++;
		height[0] = 0;
		for(int i = 1; i<N; i++)
			cin >> height[i];
		height[N] = 0;
		
		for(int i = 0; i<=N; )
		{
			//printf("i= %d\n", i);
			if(s.empty() || height[i] > height[s.top()])
			{
				s.push(i++);
			}
			else if (height[i] == height[s.top()]) {
				s.pop();
				s.push(i++);
			}
			else if(height[i] < height[s.top()])
			{
				int cur = s.top();
				s.pop();
				long long int A = height[cur] * (i - s.top() - 1);
				biggest = biggest > A ? biggest : A;
			}
		}
		
		printf("%lld\n", biggest);
	}
}
