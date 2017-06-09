#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include "majority.h"
using namespace std;

#define MASTER_NODE 0

int main() {
    int nodes = NumberOfNodes();
    int id = MyNodeId();

    long long N = GetN();
    long long work_per_node = N / nodes + (N % nodes ? 1 : 0);
    long long beg = work_per_node * id;
    long long end = work_per_node * (id + 1);
    if (end > N)
        end = N;

    if (work_per_node == 1) {
        nodes = N;
        if (id >= nodes)
            return 0;
        if (N == 1) {
            printf("%lld\n", max(0LL, GetVote(0)));
            return 0;
        }
    }

    deque<long long> d(end - beg);
    long long winner = GetVote(beg);
    d[0] = winner;
    long long votes = 1;
    for (long long i = beg + 1; i < end; ++i) {
        long long v = GetVote(i);
        d[i - beg] = v;
        if (v == winner)
            ++votes;
        else {
            --votes;
            if (votes < 0) {
                votes = 1;
                winner = v;
            }
        }
    }
    for (int n = 0; n < nodes; ++n) {
        PutLL(n, winner);
        Send(n);
    }
    // Local winner sent

    unordered_map<long long, long long> m;
    for (int n = 0; n < nodes; ++n) {
        int from = Receive(-1);
        long long w = GetLL(from);
        m[w] = 0;
    }

    for (long long i = beg; i < end; ++i) {
        long long v = d[i - beg];// GetVote(i);
        auto el = m.find(v);
        if (el != m.end()) {
            ++(el->second);
        }
    }
    if (id != MASTER_NODE) {
        for (auto el : m) {
            PutLL(MASTER_NODE, el.first);
            PutLL(MASTER_NODE, el.second);
        }
        Send(MASTER_NODE);
    }


    if (id == MASTER_NODE) {
        for (int n = 1; n < nodes; ++n) {
            int from = Receive(n);
            for (int i = 0; i < m.size(); ++i) {
                long long w = GetLL(from);
                long long v = GetLL(from);
                m[w] += v;
            }
        }

        long long winner = -1;
        long long votes = 0;
        for (auto el: m) {
            long long w = el.first;
            long long v = el.second;
            if (v > votes) {
                votes = v;
                winner = w;
            }
        }

        if (votes > N / 2)
            printf("%lld\n", winner);
        else
            printf("NO WINNER\n");
    }

    return 0;
}