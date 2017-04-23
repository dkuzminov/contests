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
    unsigned Result;

    int N, P;
    vector<long long> R;
    vector<vector<long long>> Q;

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
    cin >> N >> P;
    R.resize(N);
    Q.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> R[i];
    }
    for (int i = 0; i < N; ++i) {
        Q[i].resize(P);
        for (int j = 0; j < P; ++j) {
            cin >> Q[i][j];
        }
    }
}

void TTestCase::Run()
{
    Result = 0;

    for (int i = 0; i < N; ++i) {
        sort(Q[i].begin(), Q[i].end());
    }

    std::vector<pair<long long, long long>> s1;
    for (int j = 0; j < P; ++j) {
        long long mn = Q[0][j] / 1.1 / R[0];
        long long mx = Q[0][j] / 0.9 / R[0];
        while (mn * R[0] * 1.1 < Q[0][j])
            ++mn;
        while (mx * R[0] * 0.9 > Q[0][j])
            --mx;
        if (mn <= mx)
            s1.push_back(make_pair(mn, mx));
    }

    for (int i = 1; i < N; ++i) {
        std::vector<pair<long long, long long>> s2;
        for (int j = 0; j < P; ++j) {
            long long mn = Q[i][j] / 1.1 / R[i];
            long long mx = Q[i][j] / 0.9 / R[i];
            while (mn * R[i] * 1.1 < Q[i][j])
                ++mn;
            while (mx * R[i] * 0.9 > Q[i][j])
                --mx;
            if (mn <= mx)
                s2.push_back(make_pair(mn, mx));
        }
        std::vector<pair<long long, long long>> s3;
        for (int k = 0, l = 0; k < s1.size() && l < s2.size();) {
            long long mn = max(s1[k].first, s2[l].first);
            long long mx = min(s1[k].second, s2[l].second);
            if (mn <= mx) {
                s3.push_back(make_pair(mn, mx));
                ++k, ++l;
            }
            else if (s1[k].second < s2[l].first) {
                ++k;
            }
            else {
                ++l;
            }
        }
        swap(s1, s3);
    }

    Result = s1.size();
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
