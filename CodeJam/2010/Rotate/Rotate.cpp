
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


struct CELL
{
    char Color;
    int N, NE, E, SE, S, SW, W, NW;
    CELL()
    {
        N = NE = E = SE = S = SW = W = NW = -1;
    }
};

class BOARD
{
private:
    vector<CELL> Cells;
    CELL FakeCell;
public:
    BOARD(int n)
        : N(n)
    {
        Cells.resize(n*n);
        FakeCell.Color = '.';
    }
    CELL& Get( int i, int j )
    {
        if( i>=0 && j>=0 && i<N && j<N )
        {
            return Cells[i*N + j];
        }
        else
        {
            return FakeCell;
        }
    }

    int N;
};


void PrintBoard( BOARD& b )
{
    for(int i =0; i<b.N; ++i )
    {
        for(int j =0; j<b.N; ++j )
        {
            cout << b.Get(i,j).Color;
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

int K;
bool Red, Blue;

void Check( char color, int k )
{
    if( k >= K )
    {
        switch( color )
        {
        case 'R':
            Red = true;
            break;
        case 'B':
            Blue = true;
        }
    }
}

int GetN( BOARD& board, int i, int j )
{
    CELL& cell = board.Get(i,j);
    if( cell.Color == '.' )
        return -1;
    if( cell.N != -1 )
        return cell.N;
    CELL& cellN = board.Get(i-1,j);
    if( cellN.Color == cell.Color )
    {
        cell.N = GetN( board, i-1, j ) + 1;
    }
    else
    {
        cell.N=0;
    }

    Check( cell.Color, cell.N+1 );
    return cell.N;
}

int GetNE( BOARD& board, int i, int j )
{
    CELL& cell = board.Get(i,j);
    if( cell.Color == '.' )
        return -1;
    if( cell.NE != -1 )
        return cell.NE;
    CELL& cellNE = board.Get(i-1,j+1);
    if( cellNE.Color == cell.Color )
    {
        cell.NE = GetNE( board, i-1, j+1 ) + 1;
    }
    else
    {
        cell.NE=0;
    }

    Check( cell.Color, cell.NE+1 );
    return cell.NE;
}

int GetE( BOARD& board, int i, int j )
{
    CELL& cell = board.Get(i,j);
    if( cell.Color == '.' )
        return -1;
    if( cell.E != -1 )
        return cell.E;
    CELL& cellE = board.Get(i,j+1);
    if( cellE.Color == cell.Color )
    {
        cell.E = GetE( board, i, j+1 ) + 1;
    }
    else
    {
        cell.E=0;
    }

    Check( cell.Color, cell.E+1 );
    return cell.E;
}

int GetSE( BOARD& board, int i, int j )
{
    CELL& cell = board.Get(i,j);
    if( cell.Color == '.' )
        return -1;
    if( cell.SE != -1 )
        return cell.SE;
    CELL& cellSE = board.Get(i+1,j+1);
    if( cellSE.Color == cell.Color )
    {
        cell.SE = GetSE( board, i+1, j+1 ) + 1;
    }
    else
    {
        cell.SE=0;
    }

    Check( cell.Color, cell.SE+1 );
    return cell.SE;
}

int GetS( BOARD& board, int i, int j )
{
    CELL& cell = board.Get(i,j);
    if( cell.Color == '.' )
        return -1;
    if( cell.S != -1 )
        return cell.S;
    CELL& cellS = board.Get(i+1,j);
    if( cellS.Color == cell.Color )
    {
        cell.S = GetS( board, i+1, j ) + 1;
    }
    else
    {
        cell.S=0;
    }

    Check( cell.Color, cell.S+1 );
    return cell.S;
}

int GetSW( BOARD& board, int i, int j )
{
    CELL& cell = board.Get(i,j);
    if( cell.Color == '.' )
        return -1;
    if( cell.SW != -1 )
        return cell.SW;
    CELL& cellSW = board.Get(i+1,j-1);
    if( cellSW.Color == cell.Color )
    {
        cell.SW = GetSW( board, i+1, j-1 ) + 1;
    }
    else
    {
        cell.SW=0;
    }

    Check( cell.Color, cell.SW+1 );
    return cell.SW;
}

int GetW( BOARD& board, int i, int j )
{
    CELL& cell = board.Get(i,j);
    if( cell.Color == '.' )
        return -1;
    if( cell.W != -1 )
        return cell.W;
    CELL& cellW = board.Get(i,j-1);
    if( cellW.Color == cell.Color )
    {
        cell.W = GetW( board, i, j-1 ) + 1;
    }
    else
    {
        cell.W=0;
    }

    Check( cell.Color, cell.W+1 );
    return cell.W;
}

int GetNW( BOARD& board, int i, int j )
{
    CELL& cell = board.Get(i,j);
    if( cell.Color == '.' )
        return -1;
    if( cell.NW != -1 )
        return cell.NW;
    CELL& cellNW = board.Get(i-1,j-1);
    if( cellNW.Color == cell.Color )
    {
        cell.NW = GetNW( board, i-1, j-1 ) + 1;
    }
    else
    {
        cell.NW=0;
    }

    Check( cell.Color, cell.NW+1 );
    return cell.NW;
}


int main()
{
    cin.rdbuf( fsIn.rdbuf() );

    int T;
    cin >> T;

	for( int caseNum = 1; caseNum <= T; ++caseNum )
	{
		int N;
        cin >> N >> K;

        BOARD board(N);
        for( int i=0; i<N; ++i )
        {
            for( int j=0; j<N; ++j )
            {
                char c;
                cin >> c;
                board.Get(i, j).Color = c;
            }
        }

        PrintBoard( board );

        BOARD boardRotated(N);
        for( int i=0; i<N; ++i )
        {
            for( int j=0; j<N; ++j )
            {
                boardRotated.Get(j, N-i-1).Color = board.Get(i, j).Color;
            }
        }

        PrintBoard( boardRotated );

        for( int j=0; j<N; ++j )
        {
            int free = N-1;
            while( free >= 0 && boardRotated.Get( free, j).Color != '.')
            {
                --free;
            }
            for( int i=free-1; i>=0; --i )
            {
                if( boardRotated.Get(i,j).Color != '.' )
                {
                    boardRotated.Get( free--, j ).Color = boardRotated.Get(i,j).Color;
                }
            }
            while( free >= 0 )
            {
                boardRotated.Get( free--, j ).Color = '.';
            }

        }

        PrintBoard( boardRotated );


        Red = Blue = false;
        for( int i=0; i<N; ++i )
        {
            for( int j=0; j<N; ++j )
            {
                GetN( boardRotated, i, j );
                GetNE( boardRotated, i, j );
                GetE( boardRotated, i, j );
                GetSE( boardRotated, i, j );
                GetS( boardRotated, i, j );
                GetSW( boardRotated, i, j );
                GetW( boardRotated, i, j );
                GetNW( boardRotated, i, j );
            }
        }



        cout << "Case #" << caseNum << ": ";
        fsOut << "Case #" << caseNum << ": ";
        if( Red && Blue )
        {
            cout << "Both" << endl;
            fsOut << "Both" <<  endl;
        }
        else if( Red && !Blue )
        {
            cout << "Red" << endl;
            fsOut << "Red" <<  endl;
        }
        else if( !Red && Blue )
        {
            cout << "Blue" << endl;
            fsOut << "Blue" <<  endl;
        }
        else
        {
            cout << "Neither" << endl;
            fsOut << "Neither" <<  endl;
        }
	}
    for(;;);
	return 0;
}

