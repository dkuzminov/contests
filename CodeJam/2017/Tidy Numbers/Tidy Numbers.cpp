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

#define TASKNUM "B"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    string Result;

    string N;

    void Go(int i);
    void Trunc();

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
    cin >> N;
}




void TTestCase::Go(int i) {
    if (i == N.size() - 1)
        return;

    if (N[i] < N[i + 1]) {
        Go(i + 1);
    }
    else if (N[i] == N[i + 1]) {
        Go(i + 1);
        if (N[i] > N[i + 1]) {
            --N[i];
            N[i + 1] = '9';
        }
    }
    else {
        --N[i];
        for (int j = i + 1; j < N.size(); ++j)
            N[j] = '9';
    }
}

void TTestCase::Trunc() {
    while (Result.front() == '0') {
        Result.erase(0, 1);
    }
}

void TTestCase::Run()
{
    Go(0);
    Result = N;
    Trunc();
}


TTestCase::~TTestCase()
{
    cout << Result << endl;
    fsOut << Result << endl;
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
