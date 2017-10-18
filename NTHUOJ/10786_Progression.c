#include <stdio.h>

int main()
{
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	if(b-a == c-b) printf("%d %d", 2*a - b, c + (b-a));
	else printf("%d %d", a/(b/a), c*(b/a));
}
