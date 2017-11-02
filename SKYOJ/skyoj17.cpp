// 卦長遊戲：序章

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

queue< pair<int, int> > status;
set<int> visit;
int target[3][3];
int source[3][3];

int main (void)
{
	//cin.tie(0);
	//ios::sync_with_stdio(false);
	int T;
	cin >> T;
	int targetValue = 0, targetInversion = 0;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		{
			cin >> target[i][j];
			targetValue *= 10;
			targetValue += target[i][j];
		}

	for(int i = 0; i < 9; i++)
	{
		for(int j = i + 1; j < 9; j++)
		{
			if(target[i / 3][i % 3] == 0 || target[j / 3][j % 3] == 0) continue;
			if(target[i / 3][i % 3] > target[j / 3][j % 3]) targetInversion++;
		}
	}



	while(T--)
	{
		// init
		while(!status.empty()) status.pop();
		visit.clear();

		int s = 0, sourceInversion = 0;
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
			{
				cin >> source[i][j];
				s *= 10;
				s += source[i][j];
			}


		for(int i = 0; i < 9; i++)
		{
			for(int j = i + 1; j < 9; j++)
			{
				if(source[i / 3][i % 3] == 0 || source[j / 3][j % 3] == 0) continue;
				if(source[i / 3][i % 3] > source[j / 3][j % 3]) sourceInversion++;
			}
		}
		int diff = (sourceInversion - targetInversion);
		diff = diff < 0 ? -diff : diff;

		if(diff % 2 == 0) status.push(make_pair(s, 0));

		// bfs
		bool result = false;
		while(!status.empty())
		{
			int cur = status.front().first;
			int step = status.front().second;
			int x, y;
			status.pop();

			// Result!
			if(cur == targetValue)
			{
				cout << step << "\n";
				result = true;
				break;
			}

			// visited?
			if(visit.count(cur) > 0) continue;
			// visit it!
			visit.insert(cur);

			// make it back
			for(int i = 2; i >= 0; i--)
				for(int j = 2; j >= 0; j--)
				{
					source[i][j] = cur % 10;
					if(source[i][j] == 0) y = i, x = j;
					cur /= 10;
				}

			// UP
			if(y != 0)
			{
				source[y][x] = source[y - 1][x];
				source[y - 1][x] = 0;
				int temp = 0;
				for(int i = 0; i < 3; i++)
					for(int j = 0; j < 3; j++)
					{
						temp *= 10;
						temp += source[i][j];
					}
				status.push(make_pair(temp, step + 1));

				source[y - 1][x] = source[y][x];
				source[y][x] = 0;
			}
			// DOWN
			if(y != 2)
			{
				source[y][x] = source[y + 1][x];
				source[y + 1][x] = 0;
				int temp = 0;
				for(int i = 0; i < 3; i++)
					for(int j = 0; j < 3; j++)
					{
						temp *= 10;
						temp += source[i][j];
					}
				status.push(make_pair(temp, step + 1));

				source[y + 1][x] = source[y][x];
				source[y][x] = 0;
			}
			// LEFT
			if(x != 0)
			{
				source[y][x] = source[y][x - 1];
				source[y][x - 1] = 0;
				int temp = 0;
				for(int i = 0; i < 3; i++)
					for(int j = 0; j < 3; j++)
					{
						temp *= 10;
						temp += source[i][j];
					}
				status.push(make_pair(temp, step + 1));

				source[y][x - 1] = source[y][x];
				source[y][x] = 0;
			}
			// RIGHT
			if(x != 2)
			{
				source[y][x] = source[y][x + 1];
				source[y][x + 1] = 0;
				int temp = 0;
				for(int i = 0; i < 3; i++)
					for(int j = 0; j < 3; j++)
					{
						temp *= 10;
						temp += source[i][j];
					}
				status.push(make_pair(temp, step + 1));

				source[y][x + 1] = source[y][x];
				source[y][x] = 0;
			}
		}
		if(!result) cout << "MS\n";
	}
}

