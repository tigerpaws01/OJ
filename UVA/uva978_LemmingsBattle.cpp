#include <cstdio>
#include <iostream>
#include <queue>
#define MAX 100000
using namespace std;

struct BattleGround{
	int g, b;
};

int N, B, SG, SB;
priority_queue<int> blue, green;
BattleGround battle[105];

int main()
{
	
	cin >> N;
	while(N--)
	{
		cin >> B >> SG >> SB;
		
		for(int i = 0; i<SG; i++)
		{
			int temp;
			cin >> temp;
			green.push(temp);
		} 
		for(int i = 0; i<SB; i++)
		{
			int temp;
			cin >> temp;
			blue.push(temp);
		}
		
		for(int i = 0; i<B; i++) battle[i].b = 0, battle[i].g = 0;
		
		while(!blue.empty() && !green.empty())
		{
			#ifdef DEBUG
				cout << "\n---- Advance ----\n";
			#endif
			for(int i = 0; i<B; i++)
			{
				// Advance!
				if(!blue.empty()) battle[i].b = blue.top(), blue.pop();
				if(!green.empty()) battle[i].g = green.top(), green.pop();
				#ifdef DEBUG
					cout << "For battle field " << i << ":\n";
					cout << " > Blue  sent " << battle[i].b << " on the field!\n";
					cout << " > Green sent " << battle[i].g << " on the field!\n";
				#endif
				// Fight!
				if(battle[i].g > battle[i].b)
					battle[i].g = battle[i].g - battle[i].b, battle[i].b = 0;
				else if(battle[i].g < battle[i].b)
					battle[i].b = battle[i].b - battle[i].g, battle[i].g = 0;
				else
					battle[i].g = battle[i].b = 0;
					
			}
			#ifdef DEBUG
				cout << "\n---- Retreat ----\n";
			#endif
			// Retreat
			for(int i = 0; i<B; i++)
			{
				#ifdef DEBUG
					cout << "For battle field " << i << ":\n";
					cout << " > Remaining " << " B: " << battle[i].b << ", G: " << battle[i].g << '\n';
				#endif
				if(battle[i].g > 0) green.push(battle[i].g), battle[i].g = 0;
				else if(battle[i].b > 0) blue.push(battle[i].b), battle[i].b = 0;
				#ifdef DEBUG
					cout << " > For now, Soldiers are, B: " << blue.size() << ", G: " << green.size() << '\n';
				#endif
			}
		}
		
		if(blue.empty() && green.empty())
			cout << "green and blue died\n";
		else
		{
			#ifdef DEBUG
				cout << "\nResult :\nB: " << blue.size() << ", G: " << green.size() << "\n--------\n";
			#endif
			cout << (!blue.empty() ? "blue" : "green") << " wins\n";
			
			while(!blue.empty())
			{
				cout << blue.top() << '\n';
				blue.pop();
			}
			while(!green.empty())
			{
				cout << green.top() << '\n';
				green.pop();
			}
		}
		if(N > 0) cout << '\n';
			
	}
}
