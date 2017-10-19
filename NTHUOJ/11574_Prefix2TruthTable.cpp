#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

char str[1000];
bool input[26];
int pos;

void Process(int num, int total);
bool calculate();

void Process(int num, int total)
{
	if(num < total)
	{
		input[num] = false;
		Process(num+1, total);
		
		input[num] = true;
		Process(num+1, total);
	}
	else
	{
		pos = 0;
		if(calculate())
		{
			for(int i = 0; i<total; i++)
				cout << (input[i] ? 1 : 0) << " ";
			cout << "\n";
		}
	}
}

bool calculate()
{
	bool l, r;
	switch(str[pos])
	{
		case '&':
			pos++;
			l = calculate(),
			r = calculate();
			return l && r;
			break;
		case '|':
			pos++;
			l = calculate(),
			r = calculate();
			return l || r;
			break;
		case '^':
			pos++;
			l = calculate(),
			r = calculate();
			return l != r;
			break;
		default:
			return input[ str[pos++]-'A' ];
	}
}

int main()
{
	int num, length;
	
	cin >> num >> length;
	cin >> str;
	Process(0, num);
}
