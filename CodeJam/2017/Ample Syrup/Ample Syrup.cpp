#include <algorithm>
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

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

const double pi = 3.1415926535897;

double square1(double r, double h) {
    return 2 * pi * r * h;
}

class TTestCase
{
private:
    double Result;

    int N, K;
    vector<pair<int, int>> P;

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
    P.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i].first >> P[i].second;
    }
}

bool TTestCase::Solve()
{
    sort(P.begin(), P.end(),
        [](pair<int, int> a, pair<int, int> b) {
            return square1(a.first, a.second) > square1(b.first, b.second);
        });
    Result = 0;
    int largestR = 0;
    for (int i = 0; i < K - 1; ++i) {
        Result += square1(P[i].first, P[i].second);
        if (P[i].first > largestR)
            largestR = P[i].first;
    }
    double subResult = Result;
    for (int i = K - 1; i < N; ++i) {
        int R = max(largestR, P[i].first);
        Result = max(Result, subResult + square1(P[i].first, P[i].second) + pi * R * R);
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
