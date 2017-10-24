// GRAVITY CENTRE OF A TREE
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#define MAX 100005
//#define DEBUG
using namespace std;

vector<int> edge[MAX];
//map<int, int> asdt[MAX]; // asdt[i][j] = k; => 節點i在往節點j的方向有k個子孫
vector< pair<int, int> > asdt[MAX];
int T, N;

int DFS(int target, int source = MAX)
{
	int sum = 0;
	if(edge[target].size() == 1 && edge[target].at(0) == source) // Leaf
	{
		asdt[target].push_back(make_pair(source, N-1));
		////asdt[target][source] = N-1;
		/*#ifdef DEBUG
			cout << target << " to " << source << " has " << asdt[target][source] << " ascendants.\n";
		#endif*/
		return 0;
	}
	else
	{
		sum = 0;
		for(vector<int>::iterator it = edge[target].begin(); it != edge[target].end(); it++)
		{
			if(*it == source)
			{
				//sum +=asdt[target][*it];
				continue;
			}
			int n = DFS(*it, target) + 1;
			asdt[target].push_back(make_pair(*it, n));
			////asdt[target][*it] = n;
			/*#ifdef DEBUG
				cout << target << " to " << *it << " has " << asdt[target][*it] << " ascendants.\n";
			#endif*/
			sum += n;
		}
	}
	asdt[target].push_back((make_pair(source, N-sum-1)));
	////asdt[target][source] = N-sum-1;
	/*#ifdef DEBUG
		cout << target << " to " << source << " has " << asdt[target][source] << " ascendants.\n";
	#endif*/

	return sum;
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);
	cin >> T;
	while(T--)
	{
		cin >> N;
		// init
		for(int i = 0; i < N; i++)
		{
			edge[i].clear();
			asdt[i].clear();
		}
		// get input
		for(int i = 0; i<N-1; i++)
		{
			int a, b;
			cin >> a >> b;
			edge[a].push_back(b);
			edge[b].push_back(a);
		}
		// DFS
		DFS(0);
		// Find the center of gravity
		int gravity = 0, leastSum = 1e9;
		for(int i = 0; i<N; i++)
		{
			int sum = 0;
			//for(map<int, int>::iterator it = asdt[i].begin(); it != asdt[i].end(); it++)
			//	sum = sum > it->second ? sum : it->second;
			for(vector< pair<int, int> >::iterator it = asdt[i].begin(); it != asdt[i].end(); it++)
			sum = sum > it->second ? sum : it->second;
			if(sum < leastSum)
			{
				leastSum = sum;
				gravity = i;
			}
		}
		cout << gravity << '\n';
	}
}
