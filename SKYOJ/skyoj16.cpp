// 量杯問題

#include <stdio.h>
#include <string.h>
#include <map>
#include <queue>
#include <iostream>
using namespace std;

int T, cap[5], Q;
queue< pair<long long int, int> > tree; // data, step
map<long long int, int> status;

int main()
{
	cin >> T;
	for(int i = 0; i < T; i++)
		cin >> cap[i];
	cin >> Q;

	tree.push(make_pair(0, 0));
	long long int cur;
	int step;
	bool found = false;
	while(!tree.empty())
	{
		int liquid[5];
		cur = tree.front().first;
		step = tree.front().second;
		tree.pop();
		
		for(long long int i = T - 1, test = cur; i >= 0; i--)
		{
			liquid[i] = test % 100;
			test /= 100;
		}
		
		// visited?
		if(status.count(cur) > 0) continue;
		status[cur] = step;

		// five volumes are presented!
		for(int i = 0; i < T; i++)
		{
			if(liquid[i] == Q)
			{
				//cout << "Found!" << " With step " << step << "\n";
				found = true;
				goto final;
			}
		}

		// fill i with water
		for(int i = 0; i < T; i++)
		{
			if(liquid[i] == cap[i]) // full
				continue;
			long long int temp = 0;
			for(int j = 0; j < T; j++)
			{
				temp *= 100;
				temp += (j == i ? cap[i] : liquid[j]);
			}
			tree.push(make_pair(temp, step + 1));
		}

		// i get rid of water
		for(int i = 0; i < T; i++)
		{
			if(liquid[i] == 0) // empty
				continue;
			long long int temp = 0;
			for(int j = 0; j < T; j++)
			{
				temp *= 100;
				temp += (j == i ? 0 : liquid[j]);
			}
			tree.push(make_pair(temp, step + 1));
		}

		// fill j with water in i
		for(int i = 0; i < T; i++)
		{
			for(int j = 0; j < T; j++)
			{
				if(i == j || liquid[i] == 0) continue;
				int iNewVolume = liquid[i] - (cap[j] - liquid[j]) > 0 ? liquid[i] - (cap[j] - liquid[j]) : 0;
				int jNewVolume = (liquid[i] + liquid[j] > cap[j] ? cap[j] : liquid[i] + liquid[j]);
				long long int temp = 0;
				for(int k = 0; k < T; k++)
				{
					temp *= 100;
					if(k == i) temp += iNewVolume;
					else if(k == j) temp += jNewVolume;
					else temp += liquid[k];
				}
				tree.push(make_pair(temp, step + 1));

			}
		}
	}
	
	final:
		cout << (found ? step : -1) << "\n";
		return 0;

}
