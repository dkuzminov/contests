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

class TTestCase
{
private:
    double Result;

    long D, N;
    vector<pair<long long, int>> H;

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
    cin >> D >> N;
    H.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> H[i].first >> H[i].second;
    }
}

void TTestCase::Run()
{
    sort(H.begin(), H.end());
    double t = ((double)D - H.back().first) / H.back().second;
    for (int i = N - 2; i >= 0; --i) {
        t = max(t, ((double)D - H[i].first) / H[i].second);
    }

    Result = D / t;
}


TTestCase::~TTestCase()
{
    cout << setprecision(7) << Result << endl;
    fsOut << setprecision(7) << Result << endl;
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
