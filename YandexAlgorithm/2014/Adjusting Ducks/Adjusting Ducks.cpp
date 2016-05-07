#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> v;
int max_sum = 0;

struct S
{
	int count;
	int tone;
};


int main(int argc, char* argv[])
{
	cin >> n;
	v.resize(n);
	for(int i=0; i<n; ++i)
		cin >> v[i];

	sort(v.begin(), v.end());

	S s;
	s.count = 1;
	s.tone = v.front();
	vv.push_back(s);
	for(int i=1; i<v.size(); ++i)
	{
		if(v[i] == vv.back().tone)
		{
			++vv.back().count;
		}
		else
		{
			s.count = 1;
			s.tone = v[i];
			vv.push_back(s);
		}
	}

	vector<int>	res1;
	vector<int>	res2;
	vector<int>	res3;
	for(int i=0; i<vv.size(); ++i)
	{
		if(i > 0)
		{

		}
		if(i < vv.size() - 1)
		{
		}
	}

	cout << max_sum;
	return 0;
}

