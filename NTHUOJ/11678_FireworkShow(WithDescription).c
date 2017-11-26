#include <stdio.h>

int T, n, m;
int a[2001];

// 這個函數的功能是：
// 在 beautyGrade 的值最高為「fireworkBeauty」的煙火，還有「remaining」個的時候，
// 合出總值為「total」的方法數
// 所以最後答案就是 showtime(最高的beauty值, 最高beauty值的煙火有幾個, 要求的m值);
int showtime(int fireworkBeauty, int remaining, int total)
{
	// 如果：已經找到beauty值最低的煙火(fireworkBeauty == 1)，
	// 而且，最低的煙火也沒有了(remaining == 0)，
	// （即沒有煙火可以再選了）
	// 可是，要求的值還是大於0，那麼只有0種方法可以達成
	if(fireworkBeauty == 1 && remaining == 0 && total > 0) return 0;
	
	// 那如果，要求的值是0的話，代表之前選的路達成了「1種」方法。
	if(total == 0) return 1;
	
	// 這個函數回傳這樣的答案：
	// 1. 「試著開始選比fireworkBeauty還少1的煙火，看看能合出total值的有多少種」
	// 2. 「試著從現在的fireworkBeauty的煙火中抓1個 (所以剩下的數量就-1)，
	//      並看看接下來能合出『total-fireworkBeauty』值的有多少種」
	//
	// 如果fireworkBeauty > 1，意即還可以再選更小的煙火，才去計算「1.」
	// 如果remaining > 0，意即這個beauty值的煙火至少還有一個，才去計算「2.」
	return
		(fireworkBeauty > 1 ? showtime(fireworkBeauty-1, a[fireworkBeauty-1], total) : 0) +
		(remaining > 0 ? showtime(fireworkBeauty, remaining-1, total-fireworkBeauty) : 0);
	
}

int main()
{
	scanf("%d", &T);
	// For every testcase
	while(T--)
	{
		int i, greatest = 0;
		scanf("%d%d", &n, &m);
		// init
		for(i = 0; i < 2000; i++) a[i] = 0;
		// get input
		// beauty為 k 的煙火，一共有a[k]個
		for(i = 0; i < n; i++)
		{
			// 所以每當輸入找到一個beauty為「temp」的煙火時，
			// a[temp]++;，代表beauty為「temp」的煙火數量增加1
			int temp;
			scanf("%d", &temp);
			a[temp]++;
			// 利用greatest來記錄目前找到的beauty最高的煙火
			greatest = greatest > temp ? greatest : temp;
		}
		// 答案：showtime(目前找到beauty值最高的煙火, 這種煙火的數量, 要求的m值);
		// 如果不使用greatest，第一個參數給2000也是可以，但這樣效能會稍微好一點
		printf("%d\n", showtime(greatest, a[greatest], m));
	}
}
