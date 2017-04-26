
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");


struct SNAPPER
{
    bool State;
    bool Power;
    SNAPPER() : State(false), Power(false) {}
    void Toggle(){State=!State;}
};

int main(int argc, char* argv[])
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
		int N;
        unsigned long K;
        cin >> N >> K;
        bool result;

        result = true;

        unsigned long mask = 1;

        if( N>28)
        {
            result = false;
        }
        else
        while(N--)
        {
            if(K & mask)
            {
//                result = true;
                mask <<= 1;
                continue;
            }
            else
            {
                result = false;
                break;
            }
        }

        cout << "Case #" << caseNum << ": " << (result? "ON": "OFF") << endl;
        fsOut << "Case #" << caseNum << ": " << (result? "ON": "OFF") << endl;
	}

    for(;;);
	return 0;
}

