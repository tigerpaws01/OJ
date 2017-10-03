/*
 * 這題說是在考樹，但其實用陣列模擬就可以了（因為只需要考慮節點的父節點，另外就是節點沒有儲存資料）
 */

#include <cstdio>
#include <iostream>
using namespace std;

int n[1005];

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);
	int N, times = 0;
	while(cin >> N)
	{
		times++;
		cout << "Case " << times << ":";
		// nodes
		for(int i = 1; i <= N; i++)
			cin >> n[i];
		// query
		int A, B;
		while(cin >> A >> B)
		{
			int a = A, b = B, distance = 1;
			bool found = false;
			if(A == 0 && B == 0) break;
			if(A == B)
			{
				cout << " " << 0;
				continue;
			}
			a = A, b = B;
			for(int baseD = 0; a != -1 && !found; baseD++, a = n[a])
			{
				b = B, distance = baseD;
				while(b != -1)
				{
					if(b == a)
					{
						found = true;
						break;
					}
					b = n[b];
					distance++;
				}
			}
			cout << " " << distance;
		}
		cout << "\n";
	}
}
