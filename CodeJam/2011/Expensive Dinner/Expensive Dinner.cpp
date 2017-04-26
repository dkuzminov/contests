
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i) 
#define FROM_0_TO(i,n) FOR(i,0,n) 

#define PRINT

#define TASKNUM "C"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    int Result;
    __int64 N;
	static vector<bool> Erat;
	static set<int> Primes;

    void Load();
    void Run();
    void Print();
public:
    TTestCase();
    ~TTestCase();
};
vector<bool> TTestCase::Erat;
set<int> TTestCase::Primes;


TTestCase::TTestCase()
    : Result(0)
{
	Load();

    Run();
}

void TTestCase::Load()
{
    cin >> N;
}

void TTestCase::Run()
{
	if(Primes.empty())
	{
		Erat.resize(1000000);
		for(int i=0; i<Erat.size(); ++i)
		{
			Erat[i] = true;
		}

		for(int i=1; i<Erat.size(); ++i)
		{
			if(!Erat[i])
				continue;
			for(int j=(i+1)*2; j<=Erat.size();j+=(i+1) )
			{
				Erat[j-1] = false;
			}
			Primes.insert(i+1);
		}
	}

	__int64 sqrtN = sqrt((long double) N)+1;
	for(set<int>::iterator i=Primes.begin(); i!=Primes.end(); ++i)
	{
		int prime = *i;
		if(prime > sqrtN)
			break;

		for(__int64 pe=((__int64)prime)*prime; pe<=N; pe*=prime)
		{
			++Result;
		}
	}
	if(N != 1) ++Result;
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
