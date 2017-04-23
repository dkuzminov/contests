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

class TTestCase
{
private:
    bool ResultBool;
    string Result;

    int N;
    int R, O, Y, G, B, V;

    void Load();
    bool Solve();
    void Check();
public:
    TTestCase();
    ~TTestCase();
};


TTestCase::TTestCase()
{
	Load();

    ResultBool = Solve();
}

void TTestCase::Load()
{
    cin >> N >> R >> O >> Y >> G >> B >> V;
}

bool TTestCase::Solve()
{
    int r = R;
    int o = O;
    int y = Y;
    int g = G;
    int b = B;
    int v = V;

    r -= g;
    b -= o;
    y -= v;
    if (r < 0 || b < 0 || y < 0)
        return false;

    if (r + b + y == 0 && (O && G || O && V || G && V))
        return false;

    if (G + O + V > 0 && r + b + y > 0 && (G && !r || O && !b || V && !y))
        return false;

    pair<int, char> a[] = { { r, 'R' }, { b, 'B' }, { y, 'Y' } };
    sort(a, a + 3);
    if (a[0].first + a[1].first < a[2].first)
        return false;

    while (a[0].first + a[1].first > a[2].first) {
        Result += {a[2].second, a[1].second, a[0].second};
        --a[0].first;
        --a[1].first;
        --a[2].first;
    }
    while (a[1].first > 0) {
        Result += {a[2].second, a[1].second};
        --a[1].first;
        --a[2].first;
    }
    while (a[0].first > 0) {
        Result += {a[2].second, a[0].second};
        --a[0].first;
        --a[2].first;
    }

    if (Result.empty()) {
        // Note: only one case is present
        while (g--) {
            Result.push_back('G');
            Result.push_back('R');
        }
        while (o--) {
            Result.push_back('O');
            Result.push_back('B');
        }
        while (v--) {
            Result.push_back('V');
            Result.push_back('Y');
        }
    }
    else {
        string tmp;
        swap(Result, tmp);
        for (char c : tmp) {
            if (c == 'R' && g) {
                Result.push_back(c);
                while (g) {
                    Result.push_back('G');
                    Result.push_back('R');
                    --g;
                }
            }
            else if (c == 'B' && o) {
                Result.push_back(c);
                while (o) {
                    Result.push_back('O');
                    Result.push_back('B');
                    --o;
                }
            }
            else if (c == 'Y' && v) {
                Result.push_back(c);
                while (v) {
                    Result.push_back('V');
                    Result.push_back('Y');
                    --v;
                }
            }
            else {
                Result.push_back(c);
            }
        }
    }


    return true;
}


void TTestCase::Check()
{
    if (ResultBool) {
        if (Result.size() != N)
            throw 1;
        for (int i = 0; i < N; ++i) {
            if (Result[i % N] == Result[(i + 1) % N])
                throw 2;
            if (Result[i % N] == 'G' && Result[(i + 1) % N] == 'Y')
                throw 3;
            if (Result[i % N] == 'G' && Result[(i + 1) % N] == 'B')
                throw 4;
            if (Result[i % N] == 'O' && Result[(i + 1) % N] == 'R')
                throw 5;
            if (Result[i % N] == 'O' && Result[(i + 1) % N] == 'Y')
                throw 6;
            if (Result[i % N] == 'V' && Result[(i + 1) % N] == 'R')
                throw 7;
            if (Result[i % N] == 'V' && Result[(i + 1) % N] == 'B')
                throw 8;
        }
    }
}

TTestCase::~TTestCase()
{
    Check();
    cout << (ResultBool? Result: "IMPOSSIBLE") << endl;
    fsOut << (ResultBool ? Result : "IMPOSSIBLE") << endl;
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
