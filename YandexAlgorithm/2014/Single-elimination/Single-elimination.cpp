#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;


int main(int argc, char* argv[])
{
	string s;

	long long N;
	cin >> N;
	getline(cin, s);
/*	int k=0;
	while(N != 1)
	{
		N >> 2;
		++k;
	}*/
	map<string, int> ms;
	while(--N)
	{
		getline(cin, s);
		int pos = s.find(" ");
		string team = s.substr(0, pos);
		++ms[team];
	}

	int res = 0;
	string winner = "";
	for(map<string, int>::iterator i=ms.begin(); i!= ms.end(); ++i)
	{
		if(i->second > res)
		{
			res = i->second;
			winner = i->first;
		}
	}

	cout << winner;
	return 0;
}

