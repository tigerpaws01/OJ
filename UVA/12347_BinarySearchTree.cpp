#include <cstdio>
#include <iostream>
#define MAX 1000005
#define LESS 0
#define MORE 1
using namespace std;

int preorder[MAX], N;

void PostOrder(int l, int r, int lastRoot = 9999999, int t = LESS)
{
	// Only one root
	if(l == r)
	{
		cout << preorder[l] << '\n';
		return;
	}
	
	// Root
	int root = preorder[l];
	
	// Left subtree: the greatest num less than root (ordered after root)
	int lsR;
	for(lsR = l+1; lsR < N && preorder[lsR] <= root; lsR++);
	lsR--;
	if(lsR > l) // Exists
		PostOrder(l+1, lsR, root, LESS);
		
	// Right subtree: the greatest num less/greater than LAST ROOT (ordered after left subtree)
	int rsR;
	if(t == LESS)
		for(rsR = lsR+1; rsR <= r && preorder[rsR] <= lastRoot && preorder[rsR] > root; rsR++);
	else
		for(rsR = lsR+1; rsR <= r && preorder[rsR] >= lastRoot && preorder[rsR] > root; rsR++);
	rsR--;
	if(rsR > lsR) // Exists
		PostOrder(lsR+1, rsR, root, MORE);
	
	// Print Root
	cout << root << '\n';
}

int main()
{
	N = 0;
	while(cin >> preorder[N]) N++;
	PostOrder(0, N-1, 9999999, LESS);
	return 0;
}
