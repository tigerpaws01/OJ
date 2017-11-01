#include <cstdio>
#include <iostream>
#include <string.h>
using namespace std;

char sudo[9][9];
int vaccune[50], vaccunes;

bool checkValid()
{
	bool valid = true;
	for(int i = 0;  i < 9 && valid; i++)
	{
		bool used[10];
		for(int j = 1; j <= 9; j++) used[j] = false;

		for(int j = 0; j < 9; j++)
		{
			if(sudo[i][j] != '.')
			{
				if(used[sudo[i][j] - '0'])
				{
					valid = false;
					break;
				}
				used[sudo[i][j] - '0'] = true;
			}
		}
	}
	for(int i = 0;  i < 9 && valid; i++)
	{
		bool used[10];
		for(int j = 1; j <= 9; j++) used[j] = false;

		for(int j = 0; j < 9; j++)
		{
			if(sudo[j][i] != '.')
			{
				if(used[sudo[j][i] - '0'])
				{
					valid = false;
					break;
				}
				used[sudo[j][i] - '0'] = true;
			}
		}
	}
	for(int vt = 0; vt <= 2 && valid; vt++)
	{
		for(int hz = 0; hz <= 2 && valid; hz++)
		{
			bool used[10];
			for(int j = 1; j <= 9; j++) used[j] = false;

			for(int x = hz * 3; x < hz * 3 + 3 && valid; x++)
			{
				for(int y = vt * 3; y < vt * 3 + 3 && valid; y++)
				{
					//cout << " >> (" << x << ", " << y << "): " << sudo[y][x] << "(" << used[sudo[y][x] - '0'] << ")\n";
					if(sudo[y][x] == '.') continue;
					if(used[sudo[y][x] - '0'])
					{
						valid = false;
						break;
					}
					used[sudo[y][x] - '0'] = true;
				}
			}
		}
	}
	return valid;
}

void Enumerate(int curVaccune)
{
	if(curVaccune == vaccunes)
	{
		// output

		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9 ; j ++)
			{
				cout << sudo[i][j];
			}
		}
		cout << "\n";
		throw 0;
	}

	bool usable[10];
	for(int i = 1; i <= 9; i++) usable[i] = true;
	int x = vaccune[curVaccune] % 9,
	    y = vaccune[curVaccune] / 9,
	    hz, vt;
	hz = x / 3;
	vt = y / 3;

	// Reduce possibilities
	for(int i = 0; i < 9; i++)
		if(sudo[y][i] != '.') usable[sudo[y][i] - '0'] = false;
	for(int i = 0; i < 9; i++)
		if(sudo[i][x] != '.') usable[sudo[i][x] - '0'] = false;
	for(int i = vt * 3; i < vt * 3 + 3; i++)
		for(int j = hz * 3; j < hz * 3 + 3; j++)
			if(sudo[i][j] != '.') usable[sudo[i][j] - '0'] = false;


	// Try!
	for(int i = 1; i <= 9; i++)
	{
		if(usable[i])
		{
			sudo[y][x] = i + '0';
			Enumerate(curVaccune + 1);
			sudo[y][x] = '.';
		}
	}

}

int main()
{
	char input[100];
	while(1)
	{
		// init
		vaccunes = 0;

		cin >> input;
		if(strcmp(input, "end") == 0) break;

		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 9; j++)
			{
				sudo[i][j] = input[i * 9 + j];
				if(sudo[i][j] == '.') vaccune[vaccunes++] = i * 9 + j;
			}
		// check if input is valid
		bool valid = checkValid();

		if(valid)
		{
			try
			{
				Enumerate(0);

			}
			catch (int n)
			{
				continue;
			}
		}
		cout << "No solution.\n";
	}
	return 0;
}
