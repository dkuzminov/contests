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

#define TASKNUM "C"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
    vector<double> Result;

    int N, Q;
    vector<pair<long long, int>> C;
    vector<vector<pair<int, long long>>> D;
    vector<vector<long long>> M;
    vector<pair<int, int>> Del;

    vector<vector<long long>> FW;
    vector<vector<double>> T;
    vector<vector<double>> FWT;

    void Load();
    bool Solve();
    void Check();

    bool _ResultBool;
public:
    TTestCase();
    ~TTestCase();
};


TTestCase::TTestCase()
{
	Load();

    _ResultBool = Solve();
}

void TTestCase::Load()
{
    cin >> N >> Q;
    C.resize(N);
    D.resize(N);
    Del.resize(Q);
    for (int i = 0; i < N; ++i) {
        cin >> C[i].first >> C[i].second;
    }
    for (int i = 0; i < N; ++i) {
        M.resize(N);
        for (int j = 0; j < N; ++j) {
            long long d;
            cin >> d;
            if (d != -1){
                D[i].push_back({ j, d });
                M[i].push_back(d);
            }
            else {
                M[i].push_back(100000000000LL);
            }
        }
    }
    for (int i = 0; i < Q; ++i) {
        cin >> Del[i].first >> Del[i].second;
    }
}

bool TTestCase::Solve()
{
    FW.resize(N, vector<long long>(N, 100000000000LL));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i != j)
                FW[i][j] = M[i][j];
            else
                FW[i][i] = 0;
        }
    }

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                FW[i][j] = min(FW[i][j], FW[i][k] + FW[k][j]);
            }
        }
    }

    T.resize(N, vector<double>(N, 100000000000.));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (FW[i][j] <= C[i].first)
                T[i][j] = FW[i][j] / (double) C[i].second;
        }
    }

    FWT.resize(N, vector<double>(N, 100000000000.));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i != j)
                FWT[i][j] = T[i][j];
            else
                FWT[i][i] = 0;
        }
    }
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                FWT[i][j] = min(FWT[i][j], FWT[i][k] + FWT[k][j]);
            }
        }
    }

    for (auto d: Del) {
        Result.push_back(FWT[d.first - 1][d.second - 1]);
    }
    return true;
}


void TTestCase::Check()
{
}

TTestCase::~TTestCase()
{
    Check();
    for (auto d : Result) {
        cout << setprecision(9) << d << " ";
        fsOut << setprecision(9) << d << " ";
    }
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
