
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define TASKNUM "C"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
	bool Failed;
    unsigned long Result;
    unsigned long Smallest;
    int N;
	vector<unsigned long> A;

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
	Smallest=10000000;
	Result = 0;
	for(int i=0;i<N;++i)
	{
		unsigned long ul;
		cin >> ul;
		A.push_back(ul);
		Result+=ul;
		if(Smallest > ul)
			Smallest = ul;
	}
}

void TTestCase::Run()
{
	unsigned long xor = 0;
	for(int i=0;i<N;++i)
	{
		xor ^= A[i];
	}
	if(xor != 0)
	{
		Failed = true;
	}
	else
	{
		Failed = false;
		Result -= Smallest;
	}
}


TTestCase::~TTestCase()
{
	if(Failed)
	{
		cout << "NO" << endl;
		fsOut << "NO" << endl;
	}
	else
	{
		cout << Result << endl;
		fsOut << Result << endl;
	}
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
