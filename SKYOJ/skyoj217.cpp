// 取數字 
#include<iostream>
#define TAKE 1
#define LEAVE 0
using namespace std;

int arr[1005], dp[1005][2] = {};
int T, N, K;

int result(int r, int take)
{
	if(dp[r][take] != 0) return dp[r][take];
	
	if(r == 0) 
		dp[r][take] = TAKE ? arr[0] : 0;
	else if(take == TAKE)
		if(r - K < 0) dp[r][take] = arr[r];
		else dp[r][take] = arr[r] + max(result(r-K, TAKE), result(r-K, LEAVE));
	else 
		dp[r][take] = max(result(r-1, TAKE), result(r-1, LEAVE));

	return dp[r][take];
	
}

int main()
{
	cin >> T;
	while(T--)
	{
		cin >> N >> K;
		for(int i = 0; i < N; i++) cin >> arr[i], dp[i][0] = dp[i][1] = 0;
		int r = max(result(N-1, TAKE), result(N-1, LEAVE));
		cout << r << "\n";
	}
}
