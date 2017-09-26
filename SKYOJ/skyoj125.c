#include <cstdio>
#include <iostream>
#include<vector>
#include <stdlib.h>
#include<string.h>
using namespace std;
int num[11]; // numbers of each char
vector<char> result;
char S[105];
int K;

void show()
{
	for(int i = 0; i < result.size(); i++)
	{
		putchar(result.at(i));
	}
	putchar('\n');
}


void go(int index, int thisRem, int rem)
{
	//printf("GO! index = %c, thisRem = %d, rem = %d\n", index+'A', thisRem, rem);
	if(rem == 1)
	{
		result.push_back(index + 'A');
		show();
		result.pop_back();
	}
	else
	// thisRem > rem 的情況下，thisRem = rem
	// 在 index 的位置加入 thisRem~1 個 index 字元
	// 再繼續執行下一個有效的index，thisRem為下一個有效的index的字元數，rem則是減去剛剛加入過的字元數
	{
		thisRem = (thisRem > rem ? rem : thisRem);
		for(int currentRem = thisRem; currentRem >= 1; currentRem--)
		{
			
			for(int i = 0; i < currentRem; i++)
				result.push_back(index + 'A');
			// 沒rem了就輸出
			if(rem - currentRem == 0)
			{
				show();
				for(int i = 0; i < currentRem; i++)
					result.pop_back();
				continue;
			}
			// 如果還有rem尋找下一個有效index並執行
			for(int i = index+1; i<11; i++)
			{
				// 為i的index有效：
				if(num[i] > 0)
				{
					go(i, num[i], rem-currentRem);

				}

			}
			for(int i = 0; i < currentRem; i++)
				result.pop_back();
		}
	}
}

int main()
{

	int times = 0;
	while(scanf("%s %d", S, &K) != EOF)
	{
		int len = strlen(S);
		if(times>0) putchar('\n');
		// sort and init
		//qsort((void *)S, strlen(S), sizeof(char), compare);
		// 整理
		for(int i = 0; i < 11; i++)
		{
			num[i] = 0;
		}
		for(int i = 0; i < len; i++)
		{
			num[S[i] - 'A']++;
		}
		//for(int i = 0; i < 105; i++) output[i] = false;
		result.clear();
		//usedresultIndex = 0;
		for(int i = 0; i < 11; i++)
		{
			if(num[i] == 0)continue;
			result.clear();
			go(i, num[i], K);
		}
		//go(0, num[0], K);
		times++;
	}
}
