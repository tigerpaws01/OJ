// 磚頭
#include <iostream>
#define m 1000007
using namespace std;

int enums[100005], division[100000], T, N;
int main()
{
	enums[0] = 1, enums[2] = 3;
	division[2] = 0, division[4] = 2;
	for(int i = 4; i <= 100000; i += 2)
	{
		division[i] = (2 * enums[i-4] + division[i-2]) % m;
		enums[i] = (enums[i - 2] * 3 + division[i]) % m;
	}
	cin >> T;
	while(T--)
	{
		cin >> N;
		cout << enums[N] % m << "\n";
	}
}
