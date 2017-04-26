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
    double Result;
    long long X, S, R, N;
    double t;

    struct WALKWAY
    {
        double B, E;
        double w;
    };
    vector<WALKWAY> Walkways;

    void Load();
    void Run();
    void Print();

    static bool LessW( WALKWAY& ww1, WALKWAY& ww2) {return ww1.w<ww2.w;}
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
    cin >> X >> S >> R >> t >> N;

    Walkways.reserve(N+1);
    Walkways.resize(N);
    FOR(i,0,N)
    {
        cin >> Walkways[i].B >> Walkways[i].E >> Walkways[i].w;
    }
}

void TTestCase::Run()
{
    Result = 0;
    unsigned pedestrian = 0;

    pedestrian += Walkways[0].B;
    FOR(i,1,N)
    {
        pedestrian += (Walkways[i].B - Walkways[i-1].E);
    }
    if(N > 1)
    {
        pedestrian += (X - Walkways.back().E);
    }
    
    if(pedestrian)
    {
        WALKWAY ww;
        ww.w = 0;
        ww.B=0;
        ww.E=pedestrian;
        Walkways.push_back(ww);
    };

    sort(ALL(Walkways), LessW);

    FOR(i,0,Walkways.size())
    {
        if(t)
        {
            //unsigned l = (Walkways[i].w+R)*t;
            double t1 = (Walkways[i].E - Walkways[i].B)/(Walkways[i].w+R);
            if(t1<t)
            {
                Walkways[i].B = Walkways[i].E;
                t -= t1;
                Result += t1;
            }
            else
            {
                double l = (Walkways[i].w+R)*t;
                Walkways[i].B += l;
                Result += t;
                t = 0;
            }
        }
        Result += (Walkways[i].E - Walkways[i].B)/(Walkways[i].w + S);
    }
}


TTestCase::~TTestCase()
{
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(6);
    fsOut.setf(ios::fixed,ios::floatfield);
    fsOut.precision(6);
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
