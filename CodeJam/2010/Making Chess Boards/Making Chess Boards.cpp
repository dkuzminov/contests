#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

//#define PRINT

#define TASKNUM "C"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

class TTestCase
{
    struct CELL
    {
        char C;
        int Power;
        CELL() : Power(-1) {}
    };
private:
    int M, N;
    vector<CELL> Data;
    vector<int> Boards;

    void Load();
    void Run();
    int GetPower(int i, int j);
    int Find(int &iMax, int &jMax, int lastKnownMax=100000000, int iStartAt=0, int jStartAt=0);
    void Print();
public:
    TTestCase()
    {
	    Load();
        Run();
    }
    ~TTestCase()
    {
        int size=0;
        for(int i=0; i<Boards.size(); ++i)
        {
            if(Boards[i])
                ++size;
        }

        cout << size << endl;
        fsOut << size << endl;
        for(int i=Boards.size()-1; i>=0; --i)
        {
            if(Boards[i])
            {
                cout << i+1 << " " << Boards[i] << endl;
                fsOut << i+1 << " " << Boards[i] << endl;
            }
        }
    }
};

void TTestCase::Load()
{
    cin >> M >> N;
    unsigned char c;

    Data.resize(M*N);

    for(int i=0; i<M; ++i)
    {
        for(int j=0; j<N; j+=4)
        {
            cin >> c;

            unsigned char temp = 0;
            if(c>='0' && c<='9')
            {
                temp = c-'0';
            }
            else if(c>='A' && c<='F')
            {
                temp = c-'A'+10;
            }

            Data[i*N+j+3].C = (temp & 0x1)? '1': '0';
            Data[i*N+j+2].C = (temp & 0x2)? '1': '0';
            Data[i*N+j+1].C = (temp & 0x4)? '1': '0';
            Data[i*N+j+0].C = (temp & 0x8)? '1': '0';
        }
    }
    Print();
}

int TTestCase::Find(int &iMax, int &jMax, int lastKnownMax, int iStartAt, int jStartAt)
{
    int result = 0;
    for(int i=iStartAt; i<M; ++i)
    {
        for(int j=jStartAt; j<N; ++j)
        {
            int power = GetPower(i,j);
            if( power > result)
            {
                result = power;
                iMax = i;
                jMax = j;
                if(power == lastKnownMax)
                {
                    return result;
                }
            }
        }
        jStartAt = 0;
    }
    return result;
}

void TTestCase::Run()
{
    Boards.resize(min(M,N));
    fill(Boards.begin(), Boards.end(), 0);

    int maxPower;
    int prevPower = 1000000;
    int iStart = 0, jStart = 0;
    bool continue_mode = false;
    int iMax=0, jMax=0;
    do
    {
        // Finding the biggest board:
        maxPower = Find(iMax, jMax, prevPower, iMax, jMax);
        if( maxPower != prevPower )
        {
            maxPower = Find(iMax, jMax);
            prevPower = maxPower;
        }

        // Removing:
        for(int i=iMax; i<(iMax+maxPower); ++i)
        {
            for(int j=jMax; j<(jMax+maxPower); ++j)
            {
                Data[i*N+j].C = ' ';
            }
        }

        // Clearing:
        for(int i=iMax; i<(iMax+maxPower); ++i)
        {
            for(int k=1; k<=maxPower && (i-k)>=0 && (jMax-k)>=0; ++k)
            {
                //if(Data[(i-k)*N+jMax-k].Power == -1)
                //    break;
                //if(Data[(i-k)*N+j-k].Power > 1)
                {
                    Data[(i-k)*N+jMax-k].Power = -1;
                }
                //else
                    //break;
            }
        }
        for(int j=jMax+1; j<(jMax+maxPower); ++j)
        {
            for(int k=1; k<=maxPower && (iMax-k)>=0 && (j-k)>=0; ++k)
            {
                //if(Data[(iMax-k)*N+j-k].Power == -1)
                //    break;
                //if(Data[(i-k)*N+j-k].Power > 1)
                {
                    Data[(iMax-k)*N+j-k].Power = -1;
                }
                //else
                    //break;
            }
        }
        for(int i=iMax; i<(iMax+maxPower); ++i)
        {
            for(int k=jMax-1; k>=0 && k>=jMax-maxPower; --k)
            {
                //if(Data[i*N+k].Power == -1 && Data[i*N+k].PowerH == -1)
                    //break;

                {
                    Data[i*N+k].Power = -1;
                }
                //else
                    //break;
            }
        }
        for(int j=jMax; j<(jMax+maxPower); ++j)
        {
            for(int k=iMax-1; k>=0 && k>=iMax-maxPower; --k)
            {
                //if(Data[k*N+j].Power == -1 && Data[k*N+j].PowerV == -1)
                    //break;
                //if(Data[k*N+j].PowerV > 1)
                {
                    Data[k*N+j].Power = -1;
                }
                //else
                    //break;
            }
        }
        Print();
        if(maxPower)
            ++Boards[maxPower-1];

    }
    while(maxPower>1);

    for(int i=0; i<M; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            if(Data[i*N+j].C != ' ')
            {
                ++Boards[0];
            }
        }
    }

}

int TTestCase::GetPower(int i, int j)
{
    if(Data[i*N+j].C == ' ') return 0;
    if(Data[i*N+j].Power != -1)
    {
        return Data[i*N+j].Power;
    }
    if( i == M-1 || j == N-1 )
        return 1;
    int tempPower1 = GetPower(i+1, j+1) + 1;
    if(Data[i*N+j].C != Data[(i+1)*N+(j+1)].C)
    {
        tempPower1 = 1;
    }

    int tempPower2 = GetPower(i, j+1) + 1;
    if(Data[i*N+j].C == Data[(i)*N+(j+1)].C)
    {
        tempPower2 = 1;
    }
    int tempPower3 = GetPower(i+1, j) + 1;
    if(Data[i*N+j].C == Data[(i+1)*N+(j)].C)
    {
        tempPower3 = 1;
    }

    int result = min(tempPower1, tempPower2);
    result = min(result, tempPower3);
    Data[i*N+j].Power = result;

    return result;
}

void TTestCase::Print()
{
#ifndef PRINT
    return;
#endif
    for(int i=0; i<M; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cout << Data[i*N+j].C;
        }
        cout << endl;
    }
    cout << endl;
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
	cout << "That's all";
    for(;;);
	return 0;
}
