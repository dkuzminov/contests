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
    //unsigned Result;

    int R, C;
    vector<vector<char>> F;

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
    cin >> R >> C;
    F.resize(R);
    for (int i = 0; i < R; ++i) {
        F[i].resize(C);
        for (int j = 0; j < C; ++j) {
            cin >> F[i][j];
        }
    }
}

void TTestCase::Run()
{
    for (int i = 0; i < R; ++i) {
        char c = '?';
        for (int j = 0; j < C; ++j) {
            if (F[i][j] != '?')
                c = F[i][j];
            else
                F[i][j] = c;
        }
    }
    for (int i = 0; i < R; ++i) {
        char c = '?';
        for (int j = C - 1; j >= 0; --j) {
            if (F[i][j] != '?')
                c = F[i][j];
            else
                F[i][j] = c;
        }
    }

    for (int j = 0; j < C; ++j) {
        char c = '?';
        for (int i = 0; i < R; ++i) {
            if (F[i][j] != '?')
                c = F[i][j];
            else
                F[i][j] = c;
        }
    }
    for (int j = 0; j < C; ++j) {
        char c = '?';
        for (int i = R - 1; i >= 0; --i) {
            if (F[i][j] != '?')
                c = F[i][j];
            else
                F[i][j] = c;
        }
    }
}


TTestCase::~TTestCase()
{
    cout << endl;
    fsOut << endl;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << F[i][j];
            fsOut << F[i][j];
        }
        cout << endl;
        fsOut << endl;
    }
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
