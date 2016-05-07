
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
#define DATASET "small"

ifstream fsIn(TASKNUM "-" DATASET "-practice.in.txt");
ofstream fsOut(TASKNUM "-" DATASET "-practice.out.txt");

struct NODE
{
	int weight;
	NODE *l;
	NODE *r;
	NODE(): weight(0), l(NULL), r(NULL){}
};


class TTestCase
{
private:
    int Result;

	int N, L;

	vector<bool> Switched;

	NODE* Dev;
	NODE* Sock;


	bool Go(NODE *sock, NODE *dev, int level, bool block);

    void Load();
    void Run();
    void Print();
public:
    TTestCase();
    ~TTestCase();
};


TTestCase::TTestCase()
{
	Load();

    Run();
}

NODE* Add(NODE *node, char c)
{
	//node->weight++;
	if(c == '0')
	{
		if(node->l != NULL)
		{
			node->l->weight++;
		}
		else
		{
			node->l = new NODE;
			node->l->weight = 1;
		}
		return node->l;
	}
	else
	{
		if(node->r != NULL)
		{
			node->r->weight++;
		}
		else
		{
			node->r = new NODE;
			node->r->weight = 1;
		}
		return node->r;
	}
}


void TTestCase::Load()
{
    cin >> N >> L;
	Dev = new NODE;
	Sock = new NODE;

	FOR(i,0,N)
	{
		NODE *node = Sock;
		FOR(j,0,L)
		{
			char c;
			do
			{
			  cin >> c;
			}
			while(c != '0' && c != '1');

			node = Add(node, c);
		}
	}

	FOR(i,0,N)
	{
		NODE *node = Dev;
		FOR(j,0,L)
		{
			char c;
			do
			{
			  cin >> c;
			}
			while(c != '0' && c != '1');
			node = Add(node, c);
		}
	}
}

bool TTestCase::Go(NODE *sock, NODE *dev, int level, bool block)
{
	bool res = false;
	if(level == L)
		return true;


	if(dev->l == NULL)
	{
		dev->l = new NODE();
	}
	if(dev->r == NULL)
	{
		dev->r = new NODE();
	}
	if(sock->l == NULL)
	{
		sock->l = new NODE();
	}
	if(sock->r == NULL)
	{
		sock->r = new NODE();
	}


	int oldResult = Result;

	for(;;)
	{
		if(Switched[level])
		{
			if(dev->l->weight == sock->r->weight)
			{
				res = Go(dev->l, sock->r, level+1, block);
				if(!res)
					break;
				res = Go(dev->r, sock->l, level+1, true);
				if(!res)
					break;
			}
			else if(dev->l->weight == sock->l->weight && block == false)
			{
				Switched[level] = !Switched[level];
				Result++;
				res = Go(dev->l, sock->l, level+1, true);
				if(!res)
					break;
				res = Go(dev->r, sock->r, level+1, true);
				if(!res)
					break;
			}
		}
		else
		{
			if(dev->l->weight == sock->l->weight)
			{
				res = Go(dev->l, sock->l, level+1, block);
				if(!res)
					break;
				res = Go(dev->r, sock->r, level+1, true);
				if(!res)
					break;
			}
			else if(dev->l->weight == sock->r->weight && block == false)
			{
				Switched[level] = !Switched[level];
				Result++;
				res = Go(dev->l, sock->r, level+1, true);
				if(!res)
					break;
				res = Go(dev->r, sock->l, level+1, true);
				if(!res)
					break;
			}
		}
		break;
	}

	if(res == true)
		return true;

	if(dev->l->weight == dev->r->weight)
	{
		Result = oldResult;
		Switched[level] = !Switched[level];

		for(;;)
		{
			if(Switched[level])
			{
				if(dev->l->weight == sock->r->weight)
				{
					res = Go(dev->l, sock->r, level+1, block);
					if(!res)
						break;
					res = Go(dev->r, sock->l, level+1, true);
					if(!res)
						break;
				}
				else if(dev->l->weight == sock->l->weight && block == false)
				{
					Switched[level] = true;
					Result++;
					res = Go(dev->l, sock->l, level+1, true);
					if(!res)
						break;
					res = Go(dev->r, sock->r, level+1, true);
					if(!res)
						break;
				}
			}
			else
			{
				if(dev->l->weight == sock->l->weight)
				{
					res = Go(dev->l, sock->l, level+1, block);
					if(!res)
						break;
					res = Go(dev->r, sock->r, level+1, true);
					if(!res)
						break;
				}
				else if(dev->l->weight == sock->r->weight && block == false)
				{
					Switched[level] = true;
					Result++;
					res = Go(dev->l, sock->r, level+1, true);
					if(!res)
						break;
					res = Go(dev->r, sock->l, level+1, true);
					if(!res)
						break;
				}
			}
			break;
		}
	}
	return res;
}

void TTestCase::Run()
{
	Result = 0;
	Switched.resize(L);
	fill(Switched.begin(), Switched.end(), false);

    if(!Go(Sock, Dev, 0, false))
	{
		Result = -1;
	}

}


TTestCase::~TTestCase()
{
	if(Result != -1)
	{
		cout << Result << endl;
		fsOut << Result << endl;
	}
	else
	{
		cout << "NOT POSSIBLE" << endl;
		fsOut << "NOT POSSIBLE" << endl;
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
