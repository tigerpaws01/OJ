// 筆記
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool GGMapUsed[26], SSMapUsed[26];
vector<int> GGroute[26], SSroute[26];

int main()
{
	int T, N, M;
	cin >> T;
	while(T--)
	{
		cin >> N >> M;

		// init
		int order[8] = {0, 1, 2, 3, 4, 5, 6, 7};
		bool result = false;
		for(int i = 0; i < 26; i++)
		{
			GGMapUsed[i] = false;
			SSMapUsed[i] = false;
			GGroute[i].clear();
			SSroute[i].clear();
		}

		// Input: GGMap
		for(int i = 0; i < M; i ++)
		{
			char a, b;
			cin >> a >> b;
			GGroute[a - 'A'].push_back(b - 'A');
			GGroute[b - 'A'].push_back(a - 'A');
			GGMapUsed[a - 'A'] = true;
			GGMapUsed[b - 'A'] = true;
		}
		// Input: SSMap
		for(int i = 0; i < M; i ++)
		{
			char a, b;
			cin >> a >> b;
			SSroute[a - 'a'].push_back(b - 'a');
			SSroute[b - 'a'].push_back(a - 'a');
			SSMapUsed[a - 'a'] = true;
			SSMapUsed[b - 'a'] = true;
		}
		// 地點參照
		vector<int> GG, SS;
		int GGlocations = 0, SSlocations = 0;
		for(int i = 0; i < 26; i++)
		{
			if(GGMapUsed[i]) GGlocations++, GG.push_back(i);
			if(SSMapUsed[i]) SSlocations++, SS.push_back(i);
		}
		if(GGlocations != SSlocations) goto final;
		else N = GGlocations;

		// Testing order
		// 把規規的第i個地點(GG.at(i))對應到散散的第order[i](SS.at(order[i]))個地點
		

		do
		{

			// 對於每一個規規的地點，檢查它們通往的地方
			// 這些地方必須與對應到的，散散通往的地方相同
			for(int i = 0; i < N; i++)
			{

				int visit[8] = {0};
				for(vector<int>::iterator it = GGroute[ GG.at(i) ].begin(); it != GGroute[ GG.at(i) ].end(); it++)
				{
					// 檢查 *it 是GG的第幾個
					for(int j = 0; j < GG.size(); j++)
					{
						//cout << "M\n";
						if(GG.size() > j && GG.at(j) == *it) visit[j]++;
					}

				}
				//cout << "-";
				for(vector<int>::iterator it = SSroute[ SS.at(order[i]) ].begin(); it != SSroute[ SS.at(order[i]) ].end(); it++)
				{
					// 檢查 *it 是SS的第幾個
					for(int j = 0; j < SS.size(); j++)
					{
						//cout << SS.size() << ", " << order[j] << "\n";
						if(SS.size() > order[j] && SS.at(order[j]) == *it) visit[j]++;
					}
						
				}
				//cout << "-";
				for(int j = 0; j < N; j++)
					if(visit[j] % 2) goto fail;
				//cout << "-";
			}
			succeed:
			result = true;

			fail:
			continue;
		}
		while(next_permutation(order, order + N) && !result);

		final:
		if(result) cout << "yes\n";
		else cout << "no\n";

	}
}
