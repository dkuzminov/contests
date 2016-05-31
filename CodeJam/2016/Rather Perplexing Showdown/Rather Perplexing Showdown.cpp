#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

#define PRINT

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

struct STR {
    char win;
    string str;
    STR(char c, string s) : win(c), str(s) {}
};

class TTestCase
{
private:
    bool Result;

    int N, R, S, P;
    string F;

    int r, p, s;
    bool Try(int m);
    STR* DFS(int pos, int n, long _2N);

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
    cin >> N >> R >> P >> S;
}

bool TTestCase::Try(int m) {
    r = R, p = P, s = S;
    switch (m) {
    case 'R':
        if (r-- == 0)
            return false;
        break;
    case 'P':
        if (p-- == 0)
            return false;
        break;
    case 'S':
        if (s-- == 0)
            return false;
        break;
    }

    F[0] = m;
    long _2N = 1 << N;
    if (auto res = DFS(0, N, _2N)) {
        F.swap(res->str);
    }
}

STR* TTestCase::DFS(int pos, int n, long _2N){
    _2N >>= 1;
    if (n == 0)
    {
        string tmp="?";
        tmp[0] = F[pos];
        return new STR(F[pos], tmp);
    }

    switch (F[pos]) {
    case 'R':
        if (s-- == 0)
            return NULL;
        F[pos + _2N] = 'S';
        break;
    case 'P':
        if (r-- == 0)
            return NULL;
        F[pos + _2N] = 'R';
        break;
    case 'S':
        if (p-- == 0)
            return NULL;
        F[pos] = 'P';
        F[pos + _2N] = 'S';
        break;
    }

    STR * s1, *s2;
    s1 = DFS(pos, n - 1, _2N);
    s2 = DFS(pos + _2N, n - 1, _2N);
    if (!s1 || !s2)
        return NULL;
    if (s1->str < s2->str)
        return new STR(' ', s1->str + s2->str);
    return new STR(' ', s2->str + s1->str);
}

void TTestCase::Run()
{
    F.resize(R + P + S);
    Result = true;
    if (!Try('P')) {
        if (!Try('R')) {
            if (!Try('S'))
                 Result = false;
        }
    }
}

TTestCase::~TTestCase()
{
    if (Result) {
        for (auto c: F) {
            cout << c;
            fsOut << c;
        }
        cout << endl;
        fsOut << endl;
    }
    else {
        cout << "IMPOSSIBLE" << endl;
        fsOut << "IMPOSSIBLE" << endl;
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
