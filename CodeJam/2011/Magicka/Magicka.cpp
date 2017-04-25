
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define TASKNUM "B"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    vector<char> Result;
    int N;
	vector<char> A;
	//map<char,char> C_;
	//set<char> D;
	//set<char> Inner;
	char CombineArr[9][9];
	bool OpposedArr[9][9];
	bool IsInArr[8];

	int GetInd(char c){switch(c){case 'Q':return 0;case 'W':return 1;case 'E':return 2;case 'R':return 3;
								case 'A':return 4;case 'S':return 5;case 'D':return 6;case 'F':return 7;default:return 8;}}
	char Combine(char c1, char c2){return CombineArr[GetInd(c1)][GetInd(c2)];}
	bool Opposed(char c1, char c2){return OpposedArr[GetInd(c1)][GetInd(c2)];}
	bool IsIn(char c){return IsInArr[GetInd(c)];}
	void Invoke(char c);

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
	fill(&CombineArr[0][0], &CombineArr[8][9], ' ');
	fill(&OpposedArr[0][0], &OpposedArr[8][9], false);

	int c;
	cin >> c;
	for(int i=0;i<c;++i)
	{
		char c1, c2, c3;
		cin >> c1 >> c2 >> c3;
		CombineArr[GetInd(c1)][GetInd(c2)] = c3;
		CombineArr[GetInd(c2)][GetInd(c1)] = c3;
	}
	int d;
	cin >> d;
	for(int i=0;i<d;++i)
	{
		char d1, d2;
		cin >> d1 >> d2;
		OpposedArr[GetInd(d1)][GetInd(d2)] = true;
		OpposedArr[GetInd(d2)][GetInd(d1)] = true;
	}
    cin >> N;
	A.reserve(N);
	for(int i=0;i<N;++i)
	{
		char c;
		cin >> c;
		A.push_back(c);
	}
	Result.reserve(N);
}

void TTestCase::Invoke(char c)
{
	if(Result.size()==0)
	{
		Result.push_back(c);
		//IsInArr[GetInd(c)] = true;
	}
	else
	{
		char combine = Combine(Result.back(), c);
		if( combine != ' ' )
		{
			Result.pop_back();
			Result.push_back(combine);
		}
		else
		{
			if(Opposed(Result.back(),c))
			{
				Result.clear();
				fill(&IsInArr[0], &IsInArr[8], false);
				return;
			}
			for(int i=0; i<8; ++i)
			{
				if(IsInArr[i] && OpposedArr[i][GetInd(c)])
				{
					Result.clear();
					fill(&IsInArr[0], &IsInArr[8], false);
					return;
				}
			}
			IsInArr[GetInd(Result.back())] = true;
			Result.push_back(c);
		}
	}
}

void TTestCase::Run()
{
	fill(&IsInArr[0], &IsInArr[8], false);
	for(int i=0; i<A.size(); ++i)
	{
		Invoke(A[i]);
	}
}


TTestCase::~TTestCase()
{
	cout << "[";
	fsOut << "[";
	for(int i=0;i<int(Result.size())-1; ++i)
	{
		cout << Result[i] << ", ";
		fsOut << Result[i] << ", ";
	}
	if(Result.size())
	{
		cout << Result.back();
		fsOut << Result.back();
	}
	cout << "]" << endl;
	fsOut << "]" << endl;
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
