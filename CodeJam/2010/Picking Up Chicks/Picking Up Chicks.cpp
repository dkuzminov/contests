
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define TASKNUM "B"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

struct S
{
    long X;
    int V;
};

vector<S> Data;


int main()
{
    cin.rdbuf( fsIn.rdbuf() );

    int C;
    cin >> C;

	for( int caseNum = 1; caseNum <= C; ++caseNum )
	{
        int N, K, T;
        long B;
        cin >> N >> K >> B >> T;

        Data.clear();

        Data.resize(N);

        for(int i=0; i<N; ++i)
        {
            cin >> Data[i].X;
        }
        for(int i=0; i<N; ++i)
        {
            cin >> Data[i].V;
        }

        int reached = 0;
        int slows = 0;
        int swaps = 0;

        for( int i=N-1; i>=0; --i )
        {
            if(Data[i].X + Data[i].V*T >= B)
            {
                ++reached;
                swaps += slows;
                if(reached == K)
                {
                    break;
                }
            }
            else
            {
                ++slows;
            }
        }










        cout << "Case #" << caseNum << ": ";
        fsOut << "Case #" << caseNum << ": ";
        if( reached >= K )
        {
            cout << swaps << endl;
            fsOut << swaps <<  endl;
        }
        else
        {
            cout << "IMPOSSIBLE" << endl;
            fsOut << "IMPOSSIBLE" <<  endl;
        }
	}
    for(;;);
	return 0;
}

