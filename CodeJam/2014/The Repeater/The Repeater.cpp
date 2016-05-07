
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i) 
#define FROM_0_TO(i,n) FOR(i,0,n) 

#define PRINT

#define TASKNUM "A"
#define DATASET "small"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

struct NODE
{
	int weight;
	NODE *l;
	NODE *r;
	NODE(): weight(0), l(NULL), r(NULL){}
};


class TTestCase
{
private:
    bool Result;
    int Result1;

	int N;

	vector<string> S;
	vector<char> Pattern;
	vector<vector<int> > C;



	void CreatePattern();
	bool ProceedString(int i, string &s);
	int ProceedLetter(int i);


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
	Result = true;

    cin >> N;
	string s;
	getline(cin, s);
	getline(cin, s);
	S.push_back(s);

	FOR(i, 1, N)
	{
		getline(cin, s);
		S.push_back(s);
	}
}



void TTestCase::CreatePattern()
{
	char c = -1;
	string s = S[0];
	for(int i=0; i<s.size(); ++i)
	{
		if(s[i] != c)
		{
			c = s[i];
			Pattern.push_back(c);
		}
	}
}

bool TTestCase::ProceedString(int k, string &s)
{
	int i=0;
	FOR(j,0,Pattern.size())
	{
		int count = 0;
		while(i<s.size() && Pattern[j] == s[i])
		{
			++i;
			++count;
		}
		if(count == 0)
		{
			Result = false;
			return false;
		}
		C[j][k] = count;
	}
	return true;
}

int TTestCase::ProceedLetter(int index)
{
/*	int res = 100000;
	int max = 0, min = 100;
	FOR(i,0,N)
	{
		if(C[index][i] < min)
		{
			min = C[index][i];
		}
		if(C[index][i] > max)
		{
			max = C[index][i];
		}
	}

	FOR(i,min,max+1)
	{
		int new_res=0;
		FOR(j,0,N)
			new_res += abs(C[index][j] - i);
		if(new_res < res)
		{
			res = new_res;
		}
	}

	return res;*/
	sort(C[index].begin(), C[index].end());
	int med = C[index][N/2];
	int res = 0;
	FOR(i,0,N)
	{
		res += abs(C[index][i] - med);
	}
	return res;
}

void TTestCase::Run()
{
	CreatePattern();
	C.resize(Pattern.size());
	FOR(j,0,C.size())
		C[j].resize(N);
	FOR(i,0,N)
	{
		ProceedString(i, S[i]);
	}
	if(Result == false)
		return;
	Result1 = 0;
	FOR(i,0,Pattern.size())
	{
		Result1 += ProceedLetter(i);
	}
}


TTestCase::~TTestCase()
{
	if(Result)
	{
		cout << Result1 << endl;
		fsOut << Result1 << endl;
	}
	else
	{
		cout << "Fegla Won" << endl;
		fsOut << "Fegla Won" << endl;
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
