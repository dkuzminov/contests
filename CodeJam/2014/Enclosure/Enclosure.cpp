
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

#define TASKNUM "C"
#define DATASET "small"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    int Result;

	int N, M, K;

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
    cin >> N >> M >> K;
}

void TTestCase::Run()
{
	Result = N * M;
	int n = min(N, M);
	int m = max(N, M);

	if(n == 1)
	{
		Result = K;
		return;
	}

	if(K <= 4)
	{
		Result = K;
		return;
	}


	int cap = 1;

    for(int i=3; ; i += 2)
	{
	  int per = 2 * i - 2;
	  cap += per;
	  if(cap >= K)
	  {
		  if(i <= n)
	        Result = min(Result, per);
		  break;
	  }
	  int side = i-2;
	  if(cap+side >= K)
	  {
		  if(i <= n)
	        Result = min(Result, per+1);
	  }
	}

	cap = 2;
    for(int i=4; ; i += 2)
	{
	  int per = 2 * i - 2;
	  cap += per;
	  if(cap >= K)
	  {
		  if(i <= n)
		    Result = min(Result, per);
		  break;
	  }
	  int side = i-3;
	  if(cap+side >= K)
	  {
		  if(i <= n)
	        Result = min(Result, per+1);
	  }
	}

	if(n % 2)
	{
		cap = (n/2 + 1) * (n/2 + 1) + (n/2) * (n/2);
		for(int i=0; ; i += 1)
		{
		  int per = 2*n - 2 + 2*i;
		  if(cap >= K)
		  {
			  if(n + i <= m)
				Result = min(Result, per);
              break;
		  }
    	  int side = i-2;
		  if(cap+side >= K)
		  {
			if(i <= n)
		    Result = min(Result, per+1);
		  }
		  cap += n;
		}
	}
	else
	{
		cap = ((n-1)/2 + 1) * ((n-1)/2 + 1) + ((n-1)/2) * ((n-1)/2) + n-1;
		for(int i=0; ; i += 1)
		{
		  int per = 2*n - 2 + 2*i;
		  if(cap >= K)
		  {
			  if(n-1 + i <= m)
				Result = min(Result, per);
			  break;
		  }
    	  int side = i-3;
		  if(cap+side >= K)
		  {
			if(i <= n)
		    Result = min(Result, per+1);
		  }
		  cap += n;
		}
	}

	cap = n*m;
	int per = 2*n + 2*m - 4;
	Result = min(Result, per);
    for(int i = 1; 2*i<=n ; ++i)
	{
		cap -= i;
		--per;
		if(cap >= K)
            Result = min(Result, per);
		cap -= i;
		--per;
		if(cap >= K)
            Result = min(Result, per);
		cap -= i;
		--per;
		if(cap >= K)
            Result = min(Result, per);
		cap -= i;
		--per;
		if(cap >= K)
            Result = min(Result, per);
		if(cap < K)
			break;
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
