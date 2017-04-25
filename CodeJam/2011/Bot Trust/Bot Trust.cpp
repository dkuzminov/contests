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
private:
	struct ACTION
	{
		char Who;
		int Btn;
		ACTION(char who,int btn) : Who(who),Btn(btn){}
	};
    int Result;
    int N;
	vector<ACTION> A;

    void Load();
    void Run();
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
    cin >> N;
	A.reserve(N);
	for(int i=0;i<N;++i)
	{
		char who;
		int btn;
		cin >> who >> btn;
		A.push_back(ACTION(who,btn));
	}
}

void TTestCase::Run()
{
	int bPos = 1;
	int bWhen = 0;
	int oPos = 1;
	int oWhen = 0;

	Result = 0;
	int when = 0;
	for(int i=0;i<N;++i)
	{
		if(A[i].Who == 'B')
		{
			when = max(abs(A[i].Btn-bPos)+bWhen,when)+1;
			bPos = A[i].Btn;
			bWhen = when;
		}
		else
		{
			when = max(abs(A[i].Btn-oPos)+oWhen,when)+1;
			oPos = A[i].Btn;
			oWhen = when;
		}
	}
	Result = when;
}


TTestCase::~TTestCase()
{
    cout << Result << endl;
    fsOut << Result << endl;
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
