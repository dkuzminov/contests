
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
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
    int N, S, p;
    vector<int> T;

    void Load();
    void Run();
    void Print();
	int Func(int t)
	{
		int br = t/3 + (t%3? 1: 0);
		if(br >= p)
			return 1;
		if( (t%3 == 2) && (br+1 >= p) )
			return 0;
		if( (t%3 == 0) && (br != 0) && (br+1 >= p) )
			return 0;
		return -1;
	}
public:
    TTestCase();
    ~TTestCase();
};


TTestCase::TTestCase()
    : Result(0)
{
	Load();

    Run();
}

void TTestCase::Load()
{
    cin >> N >> S >> p;
    T.resize(N);
    FOR(i,0,N)
    {
        cin >> T[i];
    }
}

void TTestCase::Run()
{
    sort(T.begin(), T.end(), greater<int>());

	int i;
	for(i=0; i<N; ++i, ++Result)
	{
		if(Func(T[i]) != 1)
		{
			break;
		}
	}
	for(; i<N; ++i, ++Result, --S)
	{
		if(S == 0)
		{
			break;
		}
		if(Func(T[i]) == -1)
		{
			break;
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
