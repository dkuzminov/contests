
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

#define TASKNUM "A"
#define DATASET "small"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    string Result;
	string G;

    void Load();
    void Run();

	char Translate(char c)
	{
		switch(c)
		{
		case ' ': return c;
		case 'a': return 'y';
		case 'b': return 'h';
		case 'c': return 'e';
		case 'd': return 's';
		case 'e': return 'o';
		case 'f': return 'c';
		case 'g': return 'v';
		case 'h': return 'x';
		case 'i': return 'd';
		case 'j': return 'u';
		case 'k': return 'i';
		case 'l': return 'g';
		case 'm': return 'l';
		case 'n': return 'b';
		case 'o': return 'k';
		case 'p': return 'r';
		case 'q': return 'z';
		case 'r': return 't';
		case 's': return 'n';
		case 't': return 'w';
		case 'u': return 'j';
		case 'v': return 'p';
		case 'w': return 'f';
		case 'x': return 'm';
		case 'y': return 'a';
		case 'z': return 'q';
		default:
			return '?';
		}
	}
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
	getline(cin, G);
	Result.resize(G.length());
}

void TTestCase::Run()
{
	for(int i=0; i<Result.size(); ++i)
	{
		Result[i] = Translate(G[i]);
	}
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
	cin.ignore(1);

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
