#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> v;
int max_sum = 0;

int GetSum(vector<int> &d, int index)
{
	vector<bool> b;
	b.resize(d.size());
	fill(b.begin(), b.end(), true);
	int result = 0;
	for(int i=d.size(); i>=1; --i)
	{
		int ind = index	% i;
		index /= i;
		int j=0;
		for(; ; ++j)
		{
			if(!b[j])
				++ind;
			if(j==ind)
				break;
		}
		b[j] = false;
		result *= 10;
		result += d[j];
	}
	return result;
}

void Do(int pos, int sum)
{
	if(pos == n)
	{
		if(max_sum < sum)
			max_sum = sum;
		return;
	}
	sum += v[pos];
	vector<int>	d;
	while(sum)
	{
		d.push_back(sum % 10);
		sum /= 10;
	}
	int count = 1;
	for(int i=1; i<=d.size(); ++i)
	{
		count *= i;		
	}
	for(int i=0; i<count; ++i)
	{
		int new_sum = GetSum(d, i);
		Do(pos+1, new_sum);
	}
}

int main(int argc, char* argv[])
{
	cin >> n;
	v.resize(n);
	for(int i=0; i<n; ++i)
		cin >> v[i];


	Do(0, 0);
	cout << max_sum;
	return 0;
}

