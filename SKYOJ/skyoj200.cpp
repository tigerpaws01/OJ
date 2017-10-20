#include<stdio.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

bool visit[3005];
vector<int> edge[3005];

void go_dfs(int n)
{
	if(visit[n]) return;
	visit[n] = true;
	for(vector<int>::iterator it = edge[n].begin(); it != edge[n].end(); it++)
	{
		go_dfs(*it);
	}
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);
	int T, N, M;
	cin >> T;
	while(T--)
	{
		cin >> N >> M;
		int dfs = 0;
		// initialization
		for(int i = 0; i<N; i++) edge[i].clear();
		for(int i = 0; i<N; i++) visit[i] = false;
		// get input
		while(M--)
		{
			int a, b;
			cin >> a >> b;
			edge[a].push_back(b);
			edge[b].push_back(a);
		}
		// BFS
		for(int i = 0; i<N; i++)
		{
			if(visit[i]) continue;
			dfs++;
			go_dfs(i);
		}
		// output
		cout << dfs << '\n';
	}
}
