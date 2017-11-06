// ADD ALL
#include <iostream>
#include <queue>
using namespace std;

typedef long long int L;

struct cmp{
	bool operator()(L a, L b)
	{
		return a > b;
	}
};
//int seq[100005];

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);
	int N;
	while(cin >> N)
	{
		priority_queue<L, vector<L>, cmp> seq;
		if(N == 0) break;

		for(int i = 0; i < N; i++)
		{
			int temp;
			cin >> temp;
			seq.push(temp);
		}
		long long int cost = 0;
		while(!seq.empty())
		{
			long long int a, b;
			a = seq.top();
			seq.pop();
			//cost += a;
			if(seq.empty()) break;
			
			b = seq.top();
			seq.pop();
			cost += a+b;
			seq.push(a + b);
		}



		cout << cost << "\n";
	}
	return 0;
}
