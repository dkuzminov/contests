#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

vector<long> K;
vector<int> C;
vector<long long> S;

void add(long k)
{
	if(k == 1)
	{
		if(K.size() == 0 || K.back() != 1)
		{
			S.push_back(K.size() == 0? 1: S.back() * K.back());
			K.push_back(1);
			C.push_back(1);
		}
		else
		{
			++C.back();
		}
	}
	else
	{
		S.push_back(K.size() == 0? 1: S.back() * K.back());
		K.push_back(k);
		C.push_back(1);
	}
}

long long query(long long x, long long y, int i)
{
	if(x == y)
		return 0;
	//if(i == -1)
	//	return 0;

	if(K[i] == 1)
	{
		long long c = C[i];
		if(x > c)
			return query(x - c, y - c, i - 1);
		if(y > c)
			return c - x + 1 + query(1, y - c, i - 1);
		return y - x;
	}
	else
	{
		long s = S[i];
		if(x == 1)
		{
			return 1 + query(1, (y - 1) % s + 1, i - 1);
		}
		else
		{
			if((y - 1) / s == (x - 1) / s)
			{
				return query((x - 1) % s + 1, (y - 1) % s + 1, i - 1);
			}
			else
			{
				return 2 + query(1, (y - 1) % s + 1, i - 1) + query(1, (x - 1) % s + 1, i - 1);
			}
		}
	}
}

long long query(long long x, long long y)
{
	if(x == y)
		return 0;
	else if(x > y)
		return query(y, x);
	else
	{
		return query(x, y, K.size() - 1);
	}
}

int main(int argc, char* argv[])
{
	int n;
	cin >> n;
	while(n--)
	{
		char c;
		cin >> c;
		if(c == '+')
		{
			long k;
			cin >> k;
			add(k);
		}
		else if(c == '?')
		{
			long long x, y;
			cin >> x >> y;
			cout << query(x, y) << endl;
		}
		else
			throw 1;
	}
	return 0;
}

