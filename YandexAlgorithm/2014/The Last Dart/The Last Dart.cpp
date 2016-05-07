#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int n, m;
vector<vector<long> > f;

long Cost(int i, int j)
{
	if(i<0 || i>=n || j<0 || j>=m)
		return 0;
	return f[i][j];
}

long Try(int i, int j)
{
	long res = 0;

	for(int ii=-1; ii<=1; ++ii)
		for(int jj=-1; jj<=1; ++jj)
			res += Cost(i+ii, j+jj);

	return res + 7*Cost(i,j);
}

int main(int argc, char* argv[])
{
	cin >> n >> m;
	f.resize(n);
	for(int i=0; i<n; ++i)
	{
		f[i].resize(m);
		for(int j=0; j<m; ++j)
		{
			cin >> f[i][j];
		}
	}

	long Result=-1, ii = 0, jj = 0;

	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			long t = Try(i, j);
			if(Result < t)
			{
				ii = i+1;
				jj = j+1;
				Result = t;
			}
		}
	}

	cout << ii << " " << jj;
	return 0;
}

