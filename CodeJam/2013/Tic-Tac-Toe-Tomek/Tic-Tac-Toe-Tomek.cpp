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

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
private:
  int Result;
  char B[4][4];
  bool HasDots;

  void Load();
  void Run();
  void Print();

  int Try(char c1, char c2, char c3, char c4);
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
  HasDots = false;
  for(int i=0; i<4; ++i)
    for(int j=0; j<4; ++j)
    {
      char c;
      cin >> c;
      B[i][j] = c;
      if(c == '.')
        HasDots = true;
    }
}

void TTestCase::Run()
{
  int res;

  res = Try(B[0][0], B[1][1], B[2][2], B[3][3]);
  if(res != 0)
  {
    Result = (res == 1)? 1: 2;
    return;
  }
  res = Try(B[3][0], B[2][1], B[1][2], B[0][3]);
  if(res != 0)
  {
    Result = (res == 1)? 1: 2;
    return;
  }

  for(int i=0; i<4; ++i)
  {
    res = Try(B[i][0], B[i][1], B[i][2], B[i][3]);
    if(res != 0)
    {
      Result = (res == 1)? 1: 2;
      return;
    }
    res = Try(B[0][i], B[1][i], B[2][i], B[3][i]);
    if(res != 0)
    {
      Result = (res == 1)? 1: 2;
      return;
    }
  }

  if(HasDots)
  {
    Result = 4;
  }
  else
  {
    Result = 3;
  }
}

int TTestCase::Try(char c1, char c2, char c3, char c4)
{
  static int C[256];
  C['X'] = C['O'] = C['.'] = C['T'] = 0;
  ++C[c1];
  ++C[c2];
  ++C[c3];
  ++C[c4];
  if(C['.'] != 0)
    return 0;
  if(C['O'] == 0)
    return 1;
  if(C['X'] == 0)
    return 2;
  return 0;
}

TTestCase::~TTestCase()
{
  switch(Result)
  {
  case 1:
    cout << "X won" << endl;
    fsOut << "X won" << endl;
    break;
  case 2:
    cout << "O won" << endl;
    fsOut << "O won" << endl;
    break;
  case 3:
    cout << "Draw" << endl;
    fsOut << "Draw" << endl;
    break;
  case 4:
    cout << "Game has not completed" << endl;
    fsOut << "Game has not completed" << endl;
    break;
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
