#include <stdio.h>

int tree[1030], n;

void Print_Inorder(int root)
{
	if(root*2 <= n) Print_Inorder(root*2); // Left subtree
	printf("%d%c", tree[root], (root == n ? '\n' : ' ')); // Root
	if(root*2 + 1 <= n) Print_Inorder(root*2 + 1); // Rigt Subtree
}

int main()
{
	int i;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &tree[i]);
	Print_Inorder(1);
}
