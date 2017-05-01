#include <algorithm>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define PRINT

#define TASKNUM "C"
#define DATASET "small"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    double Result;

    int N, K;
    double U;
    deque<double> P;

    void Load();
    bool Solve();
    void Check();

    bool _ResultBool;
public:
    TTestCase();
    ~TTestCase();
};


void TTestCase::Load()
{
    cin >> N >> K;
    cin >> U;
    P.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
    }
}

bool TTestCase::Solve()
{
    sort(P.begin(), P.end());
    double acc = P.front();
    P.pop_front();
    int improvedNum = 1;
    while (P.size() && (U + acc) / improvedNum > P[0]) {
        ++improvedNum;
        acc += P.front();
        P.pop_front();
    }

    Result = 1;
    for (auto p : P) {
        Result *= p;
    }
    for (double p = (U + acc) / improvedNum; improvedNum != 0; --improvedNum) {
        Result *= p;
    }

    return true;
}




void TTestCase::Check()
{
}

TTestCase::TTestCase()
{
    Load();

    _ResultBool = Solve();
}

TTestCase::~TTestCase()
{
    Check();
    cout.precision(7);
    fsOut.precision(7);
    cout << Result << " ";
    fsOut << Result << " ";
    cout << endl;
    fsOut << endl;
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
