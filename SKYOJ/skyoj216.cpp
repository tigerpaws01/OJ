// 塗色
#include <iostream>
#define m 1000007
using namespace std;


struct Stone
{
	long long int num[9];
};

long long int stone[100005][9];

int main()
{
	// precalc
	stone[1][1] = stone[1][4] = stone[1][6] = 1;
	for(int i = 2; i <= 100000; i++)
	{
		// 0: R-G, 1: R-R, 2: R-B
		// 3: G-R, 4: G-G
		// 5: B-R, 6: B-B
		// 7: B-G, 8: G-B
		stone[i][0] = (stone[i - 1][0] + stone[i - 1][1]) % m;
		stone[i][1] = (stone[i - 1][0] + stone[i - 1][1] + stone[i - 1][2]) % m;
		stone[i][2] = (stone[i - 1][1] + stone[i - 1][2]) % m;
		stone[i][3] = (stone[i - 1][3] + stone[i - 1][4] + stone[i - 1][8]) % m;
		stone[i][4] = (stone[i - 1][3] + stone[i - 1][4]) % m;
		stone[i][5] = (stone[i - 1][5] + stone[i - 1][6] + stone[i - 1][7]) % m;
		stone[i][6] = (stone[i - 1][5] + stone[i - 1][6]) % m;
		stone[i][7] = (stone[i - 1][5] + stone[i - 1][7]) % m;
		stone[i][8] = (stone[i - 1][3] + stone[i - 1][8]) % m;
	}
	// get input
	int T, N;
	cin >> T;
	while(T--)
	{
		cin >> N;
		long long int sum = 0;
		for(int i = 0; i < 7; i++) sum += stone[N][i];

		cout << sum % m << "\n";

	}
	return 0;
}
