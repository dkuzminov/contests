#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define PRINT

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    unsigned ResultBool;
    unsigned Result;

    string S;
    unsigned K;

    void Load();
    void Run();
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
    cin >> S >> K;
}

void TTestCase::Run()
{
    ResultBool = true;
    Result = 0;

    queue<int> flips;
    int i = 0;
    for (; i < S.size() - K + 1; ++i) {
        if (!flips.empty() && flips.front() < i) {
            flips.pop();
        }

        if (S[i] == '-' && !(flips.size() % 2) ||
            S[i] == '+' && flips.size() % 2) {
            flips.push(i + K - 1);
            ++Result;
        }
    }

    for (; i < S.size(); ++i) {
        if (!flips.empty() && flips.front() < i) {
            flips.pop();
        }

        if (S[i] == '-' && !(flips.size() % 2) ||
            S[i] == '+' && flips.size() % 2) {
            ResultBool = false;
            return;
        }
    }
}


TTestCase::~TTestCase()
{
    cout << (ResultBool ? to_string(Result) : "IMPOSSIBLE") << endl;
    fsOut << (ResultBool ? to_string(Result) : "IMPOSSIBLE") << endl;
}


int main()
{
    if (!fsIn.is_open())
    {
        cout << "No input file found";
    }
    cin.rdbuf(fsIn.rdbuf());

    int numberOfCases;
    cin >> numberOfCases;

    for (int caseNum = 1; caseNum <= numberOfCases; ++caseNum)
    {
        TTestCase testCase;


        cout << "Case #" << caseNum << ": ";
        fsOut << "Case #" << caseNum << ": ";
    }

    cout << "Finished";
    for (;;);
    return 0;
}
