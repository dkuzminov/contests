#include <message.h>
#include <stdio.h>
#include <deque>
#include "rps.h"
using namespace std;

#define MASTER_NODE 7

long long winner(long long i, long long j){
    char c1 = GetFavoriteMove(i);
    char c2 = GetFavoriteMove(j);
    if(c1 == c2)
        return i;
    if(c1 == 'R' && c2 == 'S')
        return i;
    if(c1 == 'P' && c2 == 'R')
        return i;
    if(c1 == 'S' && c2 == 'P')
        return i;
    return j;
}

int main() {
    long long N = GetN();
    long long nodes = NumberOfNodes();
    long long my_id = MyNodeId();
    long long div = 8;
    long long players = 1LL << N;

    if(nodes >= 64) {
        div = 64;
    }

    long long players_per_node = (players / div);
    if (players_per_node == 0)
	    players_per_node = 8;
    long long beg = players_per_node * my_id;
    long long end = players_per_node * (my_id + 1);
    if(end > players)
        end = players;

    if(beg >= players || beg == end) {
        PutLL(MASTER_NODE, -1);
    }
    else {
        PutLL(MASTER_NODE, 1);
        deque<long long> d1(end - beg);
        for (long long i = beg; i < end; ++i) {
            d1[i - beg] = i;
        }
        while(d1.size() > 1) {
            deque<long long> d2;
            for (long long i = 0; i < d1.size(); i+=2) {
                d2.push_back(winner(d1[i], d1[i+1]));
            }
            swap(d1, d2);
        }
        PutLL(MASTER_NODE, d1[0]);
    }
    Send(MASTER_NODE);

    if (my_id == MASTER_NODE) {
        deque<long long> d1;
        for (int node = 0; node < nodes; ++node) {
            Receive(node);
            long long received = GetLL(node);
            if(received == 1) {
                received = GetLL(node);
                d1.push_back(received);
            }
        }

        while(d1.size() > 1) {
            deque<long long> d2;
            for (long long i = 0; i < d1.size(); i+=2) {
                d2.push_back(winner(d1[i], d1[i+1]));
            }
            swap(d1, d2);
        }
        printf("%lld\n", d1[0]);
    }
    return 0;
}
