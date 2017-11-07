#include <iostream>
#include <stdlib.h>
using namespace std;

int c[10001], e[10001], order[10001];

int cmp(const void* a, const void*b)
{
	return e[*(int*) a] < e[*(int*)b];
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int N;
	while(cin >> N) {
		if(!N) break;
		
		for(int i = 0; i < N; i++) {
			cin >> c[i] >> e[i];
			order[i] = i;
		}
		
		long long int max = 0;
		long long int Csum = 0;
		
		qsort(order, N, sizeof(int), cmp);
		
		for(int i = 0; i < N; i++)
		{
			Csum += c[order[i]];
			max = max > (Csum + e[order[i]]) ? max :(Csum + e[order[i]]);
		}

		cout << max << "\n";
	}
}
