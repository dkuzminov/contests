
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i) 
#define FROM_0_TO(i,n) FOR(i,0,n) 

#define PRINT

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    double Result;
    unsigned A, B;
	vector<double> P;

	vector<double> Probs;
	vector<double> E;

	void Try(double result)
	{
		if(result < Result)
		{
			Result = result;
		}
	}

    void Load();
    void Run();
    void Print();
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
    cin >> A >> B;
	P.resize(A);
	FOR(i,0,A)
	{
		cin >> P[i];
	}

	cout.precision(10);
	fsOut.precision(10);
}

void TTestCase::Run()
{
	Probs.resize(A+1);
	double temp=1;
	Probs[0] = 1;
	FOR(i,0,A)
	{
		temp *= P[i];
		Probs[i+1] = temp;
	}

	Result = B+2;

	for(int i=A; i>=0; --i)
	{
		double temp = ((A-i)+ (B-i) + 1) * Probs[i] +
			          ((A-i)+ (B-i) + 1 + B + 1) * (1 - Probs[i]);
		Try(temp);
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
