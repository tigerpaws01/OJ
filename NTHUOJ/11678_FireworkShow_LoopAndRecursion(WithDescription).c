#include <stdio.h>

int T, n, m;
int a[2001];

// 這個函數的功能是：
// 每次選出數個 beautyGrade 的值為「fireworkBeauty」的煙火，
// 合出總值為「total」的方法數
// 所以最後答案就是 showtime(最高的beauty值, 要求的m值);
int showtime(int fireworkBeauty, int total)
{
	//printf("running: %d %d\n", fireworkBeauty, total);
	// 如果：已經找到沒有煙火可挑(fireworkBeauty == 0)，
	// 可是，要求的值還是大於0，那麼只有0種方法可以達成
	if(fireworkBeauty == 0 && total > 0) return 0;

	// 那如果，要求的值是0的話，代表之前選的路達成了「1種」方法。
	if(total == 0) return 1;

	// 這個函數回傳這樣的答案：
	// 選出 i 個 fireworkBeauty 的煙火，i 從 0 到這種煙火的總數目（或者，到總 beauty 值超過 total 為止）
	// 選出 i 個 fireworkBeauty 的煙火後，接著開始選 fireworkBeauty-1 的煙火
	// 答案是：對每一個 i ，這種煙火取 i 個之後達成總beauty值為 total 的方法數，再加起來
	// （就是這個煙火取0個、1個、2個、……之後，就選下一種煙火，達成總值為total的方法數）
	int result = 0, i;
	for(i = 0; i <= a[fireworkBeauty] && i * fireworkBeauty <= total; i++)
	{
		result += showtime(fireworkBeauty-1, total - i * fireworkBeauty);
	}
	return result;

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
		// 答案：showtime(目前找到beauty值最高的煙火, 要求的m值);
		// 如果不使用greatest，第一個參數給2000也是可以，但這樣效能會稍微好一點
		printf("%d\n", showtime(greatest, m));
	}
}
