#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <iomanip>
using namespace std;

struct Gear{
	int x, y, r;
	double rt;
};

bool connected(Gear *a, Gear *b)
{
	if(a == b) return false;
	return	(a->x - b->x) * (a->x - b->x) +
					(a->y - b->y) * (a->y - b->y) ==
					(a->r + b->r) * (a->r + b->r);
}

Gear g[1005];
vector<int> cnt[1005];
bool visit[1005];
double constantR;


bool dfs(int n, double targetR)
{
	//printf("  For %d whose rt= %.2f, set it %.2f\n", n, g[n].rt, targetR);
	if(visit[n]) return (g[n].rt == targetR); // true means good
	
	visit[n] = true;
	g[n].rt = targetR;
	bool result = true;
	for(vector<int>::iterator it = cnt[n].begin(); it != cnt[n].end(); it++)
	{
		double tr = (targetR < 0 ? 1 : -1) * constantR / g[*it].r;
		//printf("    tr=%.2f\n", tr);
		result = result && dfs(*it, tr);
	}
	return result;
}

int main()
{
	int T, N;
	cin >> T;
	while(T--)
	{
		scanf("%d", &N);
		// init
		for(int i = 0; i<N; i++)
		{
			g[i].r = 0;
			g[i].x = 0;
			g[i].y = 0;
			g[i].rt = 0;
			cnt[i].clear();
			visit[i] = false;
		}
		// input
		for(int i = 0; i<N; i++)
		{
			int x, y, r;
			scanf("%d%d%d", &x, &y, &r);
			g[i].x = x;
			g[i].y = y;
			g[i].r = r;
		}
		int P, Q;
		scanf("%d%d", &P, &Q);
		// process
		g[P-1].rt = 1.0 * Q;
		constantR = 1.0 * Q * g[P-1].r;
		//----------------------------
		// check for connections
		for(int i = 0; i<N; i++)
			for(int j = i+1; j<N; j++)
			{
				if(connected(&g[i], &g[j]))
				{
					cnt[i].push_back(j);
					cnt[j].push_back(i);
				}
			}
		// dfs
		bool result = dfs(P-1, Q);
		// output
		if(result)
		{
			double sum = 0;
			for(int i = 0; i<N; i++) sum += g[i].rt;
			cout << fixed << setprecision(2) << sum << '\n';
			//printf("%.2f\n", sum);
		}
		else printf("X\n");
	}
	
}
