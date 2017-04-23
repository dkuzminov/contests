#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define PRINT

#define TASKNUM "C"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    pair<int64_t, int64_t> Result;

    int64_t N, K;

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
    cin >> N >> K;
}




void TTestCase::Run()
{
    priority_queue<pair<int64_t, int64_t>> q;
    q.push(make_pair(N, 1));

    while (1) {
        auto pool = q.top();
        q.pop();
        while (!q.empty() && q.top().first == pool.first) {
            pool.second += q.top().second;
            q.pop();
        }
        int64_t mn = (pool.first - 1) / 2;
        int64_t mx = pool.first / 2;
        K -= pool.second;
        if (K <= 0) {
            Result = make_pair(mx, mn);
            return;
        }
        if (mn == mx) {
            q.push(make_pair(mn, pool.second * 2));
        }
        else {
            q.push(make_pair(mx, pool.second));
            q.push(make_pair(mn, pool.second));
        }
    }
}


TTestCase::~TTestCase()
{
    cout << Result.first << " " << Result.second << endl;
    fsOut << Result.first << " " << Result.second << endl;
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
