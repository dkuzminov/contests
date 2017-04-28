
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
    struct WIRE
    {
        int Left, Right;
    };
private:
    int Result;
    int N;
    vector<WIRE> Wires;

    void Run();
    static bool LeftLess( WIRE &wire1, WIRE &wire2 ) {return wire1.Left<wire2.Left;}
    static bool RightLess( WIRE &wire1, WIRE &wire2 ) {return wire1.Right<wire2.Right;}
    void Print()
    {return;
        for(int i=0; i<N; ++i )
        {
        cout << '('<< Wires[i].Left << ',' << Wires[i].Right << ") ";
        }
        cout << endl;
    }
public:
    TTestCase();
    ~TTestCase();
};


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
    for(;;);
	return 0;
}

TTestCase::TTestCase()
    : Result(0)
{
    cin >> N;

    Wires.resize(N);
    for(int i=0; i<N; ++i )
    {
        cin >> Wires[i].Left >> Wires[i].Right;
    }

    Print();

    Run();
}

void TTestCase::Run()
{
    sort(Wires.begin(), Wires.end(), LeftLess );
    Print();

    for(int i=0; i<Wires.size()-1; ++i)
        for(int j=0; j<Wires.size()-1; ++j)
        {
            if( !RightLess( Wires[j], Wires[j+1]) )
            {
                swap(Wires[j], Wires[j+1]);
                ++Result;
            }
        }
    Print();
}


TTestCase::~TTestCase()
{
    cout << Result << endl;
    fsOut << Result << endl;
}
