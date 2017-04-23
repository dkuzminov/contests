
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
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    int Result;
    unsigned A, B;
	unsigned Digits;

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
	Digits = 0;
	unsigned temp = A;
	while(temp != 0)
	{
		++Digits;
		temp /= 10;
	}
}

void TTestCase::Run()
{
	int power = 1;
	FOR(i,1,Digits) power *= 10;
	
	for(unsigned n=A; n<=B; ++n)
	{
		unsigned m=n;
		do
		{
			m = m/10 + (m%10)*power;
			if(m>B) continue;
			if(n<m) ++Result;
		}
		while( m!=n );
	}



	//for(unsigned n=A; n<B; ++n)
	//{
	//	vector<int> v;
	//	v.resize(Digits);
	//	unsigned temp = n;
	//	for(int i=Digits-1; i>=0; --i)
	//	{
	//		v[i] = temp%10;
	//		temp /= 10;
	//	}
	//	set<int> s;
	//	for(int i=1; i<Digits; ++i)
	//	{
	//		if(v[i] < v[0]) continue;
	//		unsigned m=0;
	//		for(int j=i; j<Digits; ++j)
	//		{
	//			m *= 10;
	//			m += v[j];
	//		}
	//		for(int j=0; j<i; ++j)
	//		{
	//			m *= 10;
	//			m += v[j];
	//		}
	//		if(m>B) continue;
	//		if(n<m)
	//		{
	//			if(s.find(m) == s.end())
	//			{
	//				s.insert(m);
	//				++Result;
	//			}
	//		}
	//	}
	//}

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
