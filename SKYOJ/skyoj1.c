#include <cstdio>
#include <iostream>
using namespace std;



/*
int main()
{
	long long int a, b, insertionMark = -1, top, base;
	vector<long long int> num;
	bool included = false;
	while(scanf("%lld/%lld = ?", &a, &b) == 2)
	{
		// simple situation
		if(a%b == 0)
		{
			printf("%lld\n", a/b);
			continue;
		}
		insertionMark = -1;
		num.clear();
		included = false;
		// erase negative
		if(a*b < 0)
		{
			printf("-");
			
		}
		a = (a<0 ? -a : a);
		b = (b<0 ? -b : b);
		printf("%lld.", a/b);
		a = a % b;
		// do a/b
		top = a; base = b;
		while(top != 0)
		{
			top *= 10;
			// check if this(top) was included
			for(int i=0; i<num.size() && !included; i++)
			{
				//if(top == 10)printf("WTF\n");
				//printf("the %dth num is %d\n", i, num.at(i));
				included = (num.at(i) == top);
			}
			// if included, set insertionMark and break
			if(included)
			{
				insertionMark = top;
				break;
			}
			// Normal situation
			if(top >= base)
			{
				num.push_back(top);
				top = top % base;

			}
			else
			{
				num.push_back(0);
			}
		}
		// print
		for(int i=0; i<num.size(); i++)
		{
			if(insertionMark == num.at(i))
				printf("(");
			printf("%lld", num.at(i)/base);
		}
		if(included) printf(")");
		printf("\n");
	}
}*/

int gcd(int a, int b)
{
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

int main()
{
	long long int a, b;
	while(scanf("%lld/%lld = ?", &a, &b) != EOF)
	{
		long long int nonloop, loop, mult_2 = 0, mult_5 = 0;
		if(a*b < 0)
  		putchar('-');
		a = a < 0 ? -a : a;
		b = b < 0 ? -b : b;
		// simple situation
		if(a%b == 0)
		{
			printf("%lld\n", a/b) ;
			continue;
		}
		// output decimal part
		printf("%lld.", a/b);
		a %= b;
		// simplification
		long long int gcd_n = gcd(a, b);
		a /= gcd_n; b /= gcd_n;
		// multiplication of 2, 5
		long long int tester = b;
		while(tester % 2 == 0 && a != 0) tester/=2, mult_2++;
		while(tester % 5 == 0 && a != 0) tester/=5, mult_5++;
		nonloop = max(mult_2, mult_5);
		
		for(int i = 0;i<nonloop; i++)
		{
			a*=10;
      printf("%lld", a/b );
      a%=b;
		}
		
		if(a!=0)
		{
      putchar('(');
      long long int indicator = a;
      do{
        a*=10;
        printf("%lld",a/b);
        a%=b;
      }while(indicator != a);
      putchar(')');
            
    }
		putchar('\n');
		
	}
	
}

