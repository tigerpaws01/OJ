#include <iostream>
#include <cstdio>
#define M 10000
using namespace std;


int go(int);

int main()
{
  int list[M], i, j, min, max, result;
  for(int index = 1; index <M; index++)
    list[index] = go(index);
  while(scanf("%d%d", &i, &j) != EOF)
  {
    min = i < j ? i : j;
    max = i < j ? j : i;
    result = 0;
    for(;min <= max; min++) result = result > list[min] ? result : list[min];
    cout << i << ' ' << j << ' ' << result << endl;
  }
}

int go(int n)
{
  if(n == 1) return 1;
  return 1 + (n%2 == 0 ? go(n/2) : go(3*n+1));
}
