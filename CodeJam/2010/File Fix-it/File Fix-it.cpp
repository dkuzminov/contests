
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

#define TASKNUM "A"
#define DATASET "large"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

int main()
{
    cin.rdbuf( fsIn.rdbuf() );


    int T;
    cin >> T;

	for( int caseNum = 1; caseNum <= T; ++caseNum )
	{
        int N, M;
        cin >> N >> M;

        int result = 0;

        set<string> exist;
        char temp[101];
        for(int i=0;i<N;++i)
        {
            cin>>temp;
            string path(temp+1);
/*            size_t pos = path.find("/");
            while(pos != -1)
            {
                path = path.substr(0,pos);
                pos = path.find("/");
            }*/

            exist.insert( path );
        }
        for(int i=0;i<M;++i)
        {
            cin>>temp;
            string path(temp+1);
            path += "/";
            size_t pos=0;
            do
            {
                pos = path.find("/",pos);
                string subpath = path.substr(0,pos++);
                pair<set<string>::iterator,bool> ret = exist.insert(subpath);
                if(ret.second)
                {
                    ++result;
                }
            }
            while(pos < path.size());
            //exist.insert(string(path));
        }



        cout << "Case #" << caseNum << ": ";
        fsOut << "Case #" << caseNum << ": ";
        cout << result << endl;
        fsOut << result <<  endl;
	}
    for(;;);
	return 0;
}

