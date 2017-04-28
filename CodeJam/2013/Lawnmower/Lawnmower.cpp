#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i) 
#define FROM_0_TO(i,n) FOR(i,0,n) 

#define PRINT

#define TASKNUM "B"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
  bool Result;
  int N, M;
  int F[100][100];
  int maxV[100];
  int maxH[100];

  void Load();
  void Run();
  void Print();
public:
  TTestCase();
  ~TTestCase();
};


TTestCase::TTestCase()
    : Result(0)
{
  Load();

  Run();
}

void TTestCase::Load()
{
  cin >> N >> M;
  for(int i=0; i<N; ++i)
    for(int j=0; j<M; ++j)
    {
      int num;
      cin >> num;
      F[i][j] = num;
    }
}

void TTestCase::Run()
{
  Result = true;

  for(int i=0; i<N; ++i)
    maxV[i] = 0;
  for(int i=0; i<M; ++i)
    maxH[i] = 0;

  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<M; ++j)
    {
      if(F[i][j] > maxV[i])
        maxV[i] = F[i][j];
      if(F[i][j] > maxH[j])
        maxH[j] = F[i][j];
    }
  }


  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<M; ++j)
    {
      if(F[i][j] < maxV[i] && F[i][j] < maxH[j])
      {
        Result = false;
        return;
      }
    }
  }

}

TTestCase::~TTestCase()
{
  if(Result)
  {
    cout << "YES" << endl;
    fsOut << "YES" << endl;
  }
  else
  {
    cout << "NO" << endl;
    fsOut << "NO" << endl;
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
  if(!fsIn.is_open())
  {
    cout << "No input file found";
  }
  cin.rdbuf( fsIn.rdbuf() );

  int numberOfCases;
  cin >> numberOfCases;

  for( int caseNum = 1; caseNum <= numberOfCases; ++caseNum )
  {
    TTestCase testCase;
      
    cout << "Case #" << caseNum << ": ";
    fsOut << "Case #" << caseNum << ": ";
  }
  cout << "Finished";
  for(;;);
  return 0;
}
