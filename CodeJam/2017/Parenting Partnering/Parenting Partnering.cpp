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

#define TASKNUM "B"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

double square1(double r, double h) {
    return 2 * pi * r * h;
}

class TTestCase
{
private:
    int Result;

    int Ac, Aj;
    vector<pair<int, int>> C;
    vector<pair<int, int>> J;

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
    cin >> Ac >> Aj;
    C.resize(Ac);
    J.resize(Aj);
    for (int i = 0; i < Ac; ++i) {
        cin >> C[i].first >> C[i].second;
    }
    for (int i = 0; i < Aj; ++i) {
        cin >> J[i].first >> J[i].second;
    }
}

bool TTestCase::Solve()
{
    Result = 0;

    vector<tuple<int, int, char>> v;

    int tc = 0, tj = 0;
    for (auto c : C) {
        v.push_back(make_tuple(c.first, c.second, 'C'));
        tc += c.second - c.first;
    }
    for (auto j : J) {
        v.push_back(make_tuple(j.first, j.second, 'J'));
        tj += j.second - j.first;
    }
    sort(v.begin(), v.end());

    priority_queue<int> qc;
    priority_queue<int> qj;
    int t_trans = 0;
    for (int i = 1; i < v.size(); ++i) {
        int t = get<0>(v[i]) - get<1>(v[i - 1]);
        if (get<2>(v[i]) == get<2>(v[i - 1])) {
            priority_queue<int> &q = get<2>(v[i]) == 'C' ? qc : qj;
            q.push(t);
            int &t_ = get<2>(v[i]) == 'C' ? tc : tj;
            t_ += t;
        }
        else {
            t_trans += t;
            ++Result;
        }
    }
    int t = 24 * 60 + get<0>(v.front()) - get<1>(v.back());
    if (get<2>(v.front()) == get<2>(v.back())) {
        priority_queue<int> &q = get<2>(v.front()) == 'C' ? qc : qj;
        q.push(t);
        int &t_ = get<2>(v.front()) == 'C' ? tc : tj;
        t_ += t;
    }
    else {
        t_trans += t;
        ++Result;
    }

    while (!(tc <= 720 && tj <= 720)) {
        if (tc > 720) {
            tc -= qc.top();
            qc.pop();
            Result += 2;
        }
        else {
            tj -= qj.top();
            qj.pop();
            Result += 2;
        }
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
