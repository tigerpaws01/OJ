#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct factory{
	long long int A, B;
	char name[25];
} fac;

fac f[100005];

int cmp(const void * a, const void *b)
{
	fac* A = ((fac*)a), *B = ((fac*)b);
	//return (B->A - B->B) - (A->A - B->B);
	if(A->A - A->B < B->A - B->B) return 1;
	if(A->A - A->B > B->A - B->B) return -1;
	else return 0;
}

int namecmp(const void * a, const void *b)
{
	return strcmp(((fac*)a)->name, ((fac*)b)->name);
}

int main(){
	int n, x, y, i;
	
	scanf("%d%d%d", &n, &x, &y);
	for(i = 0; i < n; i++) scanf("%s%d%d", &f[i].name, &f[i].A, &f[i].B);
	qsort(f, n, sizeof(fac), cmp);
	qsort(f, x, sizeof(fac), namecmp);
	for(i = 0; i < x; i++) printf("%s\n", f[i].name);
}
