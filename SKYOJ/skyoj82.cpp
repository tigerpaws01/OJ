#include <cstdio>
#include <iostream>
#include <queue>
#include <string.h>
#define LEN 35
using namespace std;

/*  kind:
 *  0: elder, 1: nursy, 2: kit,
 *  3: warrior, 4: appentice, 5: medicent
 *  6: deputy, 7: leader
 */

struct Cat
{
	char name[LEN];
	int age, kind;
};

struct cmp
{
	bool operator()(Cat *a, Cat *b)
	{
		bool yes = false, no = true; // yes : a has priority

		// kind
		if(a->kind < b->kind)
			return yes;
		else if(a->kind > b->kind)
			return no;

		// same kind: age!
		if(a->kind == 4 && a->age != b->age) // appentice: special case
		{
			return (a->age < b->age) ? yes : no;
		}
		else if(a->age != b->age)
		{
			return (a->age > b->age) ? yes : no; // normal: bigger age has priority.
		}

		// same kind, same age: name!
		return (strcmp(a->name, b->name) < 0 ? yes : no);

	}
};

Cat cats[10000];

int main()
{
	int N, M;
	
	
	while(cin >> N >> M)
	{
		priority_queue< Cat*, vector<Cat*>, cmp> catHeap, catHeap2;
		for(int i = 0; i<N; i++)
		{
			char kind[15];
			cin >> cats[i].name >> kind >> cats[i].age;

			if(strcmp(kind, "elder") == 0)			cats[i].kind = 0;
			else if(strcmp(kind, "nursy") == 0)		cats[i].kind = 1;
			else if(strcmp(kind, "kit") == 0)		cats[i].kind = 2;
			else if(strcmp(kind, "warrior") == 0)	cats[i].kind = 3;
			else if(strcmp(kind, "appentice") == 0)	cats[i].kind = 4;
			else if(strcmp(kind, "medicent") == 0)	cats[i].kind = 5;
			else if(strcmp(kind, "deputy") == 0)	cats[i].kind = 6;
			else if(strcmp(kind, "leader") == 0)	cats[i].kind = 7;
			catHeap.push(&cats[i]);
		}
		for(int i = 0; i<M && !catHeap.empty(); i++)
		{
			Cat *cur = catHeap.top();
			catHeap.pop();
			cout << cur->name << '\n';
		}
	}
	
}
