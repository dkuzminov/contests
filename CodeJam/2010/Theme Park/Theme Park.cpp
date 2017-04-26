
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define TASKNUM "C"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

vector<int> G;
int current;

int Get()
{
    return G[current];
}

void Pop()
{
    if( ++current == G.size() )
    {
        current = 0;
    }
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
        long R, K, N;
        cin >> R >> K >> N;
        G.clear();
        G.resize(N);

        __int64 result = 0;

        for(int i=0; i<N; ++i)
        {
            cin >> G[i];
        }
        current = 0;


        struct S
        {
            int round;
            __int64 result_before;
            S() : round(0), result_before(0) {}
        };
        vector<S> cache;
        cache.resize(N);


        for(int r=0; r<R; ++r)
        {
            S &s=cache[current];
            if(s.result_before)
            {
                __int64 vol = result - s.result_before;
                int step = r - s.round;
                while( r+step < R )
                {
                    result += vol;
                    r += step;
                }
            }
            s.result_before = result;
            s.round = r;



            int grNum = 0;
            __int64 settled = 0;

            while( grNum < G.size() )
            {
                int g = Get();
                if( settled + g <= K )
                {
                    settled += g;
                    result += g;
                    ++grNum;
                    Pop();
                }
                else
                {
                    break;
                }
            }
        }



        cout << "Case #" << caseNum << ": ";
        fsOut << "Case #" << caseNum << ": ";
        cout << result << endl;
        fsOut << result <<  endl;
	}
    for(;;);
	return 0;
}

