#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define FOR(i,a,b) for(unsigned long long i=(a);i<(b);++i) 
#define FROM_0_TO(i,n) FOR(i,0,n) 
#define ALL(a) a.begin(), a.end() 

#define PRINT

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    bool Result;
    unsigned R, C;
    vector<vector<char> > Data;

    void Load();
    void Run();
    void Print();

    bool Put(int i, int j);
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
    cin >> R >> C;

    Data.resize(R);
    FOR(i,0,R)
    {
        Data[i].resize(C);
        FOR(j,0,C)
            cin >> Data[i][j];
    }
}

void TTestCase::Run()
{
    Result = true;
    FOR(i,0,R)
        FOR(j,0,C)
        {
            if(Data[i][j] == '#')
                if(!Put(i,j))
                {
                    Result = false;
                    return;
                }
        }
}

bool TTestCase::Put(int i, int j)
{
    Data[i][j] = '/';
    if(j+1<C && Data[i][j+1] == '#') Data[i][j+1] = '\\';
    else return false;
    if(i+1<R && Data[i+1][j] == '#') Data[i+1][j] = '\\';
    else return false;
    if(Data[i+1][j+1] == '#') Data[i+1][j+1] = '/';
    else return false;
    return true;
}


TTestCase::~TTestCase()
{
    if(Result)
    {
        cout << endl;
        fsOut << endl;
        FOR(i,0,R)
        {
            FOR(j,0,C)
            {
                cout << Data[i][j];
                fsOut << Data[i][j];
            }
            cout << endl;
            fsOut << endl;
        }
    }
    else
    {
        cout << endl;
        fsOut << endl;
        cout << "Impossible" << endl;
        fsOut << "Impossible" << endl;
    }
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
