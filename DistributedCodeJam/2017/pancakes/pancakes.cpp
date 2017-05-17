#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <map>
#include "pancakes.h"
using namespace std;

#define MASTER_NODE 0

int main() {
    int nodes = NumberOfNodes();
    int nid = MyNodeId();

    long long N = GetStackSize();
    long long D = GetNumDiners();
    long long min_work_per_node = N / nodes;
    long long max_work_per_node = min_work_per_node + (N % nodes ? 1 : 0);
    long long work_per_node = (nid >= N % nodes ? min_work_per_node : max_work_per_node);

    long long beg = min_work_per_node * nid + min<long long>(N % nodes, nid);
    long long end = beg + work_per_node;

    if (beg >= N || beg == end) {
        PutLL(MASTER_NODE, 0LL);
        Send(MASTER_NODE);
        return 0;
    }


    long long res = 0;
    if (nid == MASTER_NODE) {
        long long prev = GetStackItem(0);
        for (long long i = /*0*/beg + 1; i < end; ++i) {
            long long curr = GetStackItem(i);
            if (curr < prev)
                ++res;
            prev = curr;
        }
    }
    else {
        long long prev = GetStackItem(beg - 1);
        for (long long i = beg; i < end; ++i) {
            long long curr = GetStackItem(i);
            if (curr < prev)
                ++res;
            prev = curr;
        }
    }
    PutLL(MASTER_NODE, res);
    Send(MASTER_NODE);


    if (nid == MASTER_NODE) {
        long long res = 0;
        for (int node = 0; node < nodes; ++node) {
            Receive(node);
            long long r = GetLL(node);
            res += r;
        }
        printf("%lld\n", res + 1);
    }

    return 0;
}