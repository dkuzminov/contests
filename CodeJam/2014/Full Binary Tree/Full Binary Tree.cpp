
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <iomanip>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i) 
#define FROM_0_TO(i,n) FOR(i,0,n) 

#define PRINT

#define TASKNUM "B"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    int Result;
    int N;

	vector<vector<int> > Nodes;

	int Follow(int from, int to);
    int Del(int from, int to);

	map<long, int> F;
	map<long, int> D;

    void Load();
    void Run();
    void Print();
public:
    TTestCase();
    ~TTestCase();
};


TTestCase::TTestCase()
{
	Load();

    Run();
}

void TTestCase::Load()
{
    cin >> N;
	Nodes.resize(N);
	FOR(i,0,N-1)
	{
		int x, y;
		cin >> x >> y;
		Nodes[x-1].push_back(y-1);
		Nodes[y-1].push_back(x-1);
	}
}

int TTestCase::Follow(int from, int to)
{
	if(F.count(from*1000 + to))
		return F[from*1000 + to];

	int result = N;
	if(Nodes[to].size() == 1)
	{
		return 0;
	}

	if(Nodes[to].size() >= 3)
	{
		FOR(j,0,Nodes[to].size()-1)
		{
			if(Nodes[to][j] == from)
				continue;

			FOR(k,j+1,Nodes[to].size())
			{
				if(Nodes[to][k] == from)
					continue;

				int new_result = Follow(to, Nodes[to][j]);
				new_result += Follow(to, Nodes[to][k]);
				FOR(l,0,Nodes[to].size())
				{
					if(l == j || l == k || Nodes[to][l] == from)
						continue;
					new_result += Del(to, Nodes[to][l]);
				}

				if(new_result < result)
				{
					result = new_result;
				}
			}
		}
	}
	else
	{
		result = 0;
		FOR(l,0,Nodes[to].size())
		{
			if(Nodes[to][l] == from)
				continue;
			result += Del(to, Nodes[to][l]);
		}
	}
	F[from*1000 + to] = result;
	return result;
}

int TTestCase::Del(int from, int to)
{
	if(D.count(from*1000 + to))
		return D[from*1000 + to];

	int result = 1;
	FOR(l,0,Nodes[to].size())
	{
		if(Nodes[to][l] == from)
			continue;
		result += Del(to, Nodes[to][l]);
	}
	D[from*1000 + to] = result;
	return result;
}

void TTestCase::Run()
{
	Result = N;

	if(N == 2)
		Result = 1;

	FOR(i,0,N)
	{
		if(Nodes[i].size() == 1)
		{
			continue;
		}


		if(Nodes[i].size() >= 2)
		{
			int dell_all_cost = 0;
	        FOR(l,0,Nodes[i].size())
			{
				dell_all_cost += Del(i, Nodes[i][l]);
			}

			FOR(j,0,Nodes[i].size()-1)
			{
				FOR(k,j+1,Nodes[i].size())
				{
					int new_result = Follow(i, Nodes[i][j]);
					if(new_result >= Result)
						continue;
					new_result += Follow(i, Nodes[i][k]);
					if(new_result >= Result)
						continue;
/*					FOR(l,0,Nodes[i].size())
					{
						if(l == j || l == k)
							continue;
						new_result += Del(i, Nodes[i][l]);
					}*/
					new_result += dell_all_cost;
					new_result -= Del(i, Nodes[i][j]);
					new_result -= Del(i, Nodes[i][k]);

					if(new_result < Result)
					{
						Result = new_result;
					}
				}
			}
		}
		else
		{
			int new_result = 0;
			FOR(l,0,Nodes[i].size())
			{
				new_result += Del(i, Nodes[i][l]);
			}

			if(new_result < Result)
			{
				Result = new_result;
			}
		}
	}
}


TTestCase::~TTestCase()
{
	cout << Result << endl;
	fsOut << Result << endl;
}

void TTestCase::Print()
{
#ifndef PRINT
    return;
#endif
}








int main()
{
    if(!fsIn.is_open())
    {
        cout << "No input file found";
    }
    cin.rdbuf( fsIn.rdbuf() );

    int numberOfCases;
    cin >> numberOfCases;

	for( int caseNum = 1; caseNum <= numberOfCases; ++caseNum )
	{
        TTestCase testCase;

        
        cout << "Case #" << caseNum << ": ";
        fsOut << "Case #" << caseNum << ": ";
	}
	
	cout << "Finished";
    for(;;);
	return 0;
}
