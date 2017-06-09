#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <map>
#include "almost_sorted.h"
using namespace std;

#define MASTER_NODE 0

int main() {
    int nodes = NumberOfNodes();
    int nid = MyNodeId();

    long long N = NumberOfFiles();
    long long K = MaxDistance();
    long long work_per_node = N / nodes + (N % nodes ? 1 : 0);
    long long beg = work_per_node * nid;
    long long end = work_per_node * (nid + 1);
    if (end > N)
        end = N;

    if (beg >= N || beg == end) {
        PutLL(MASTER_NODE, 0LL);
        Send(MASTER_NODE);
        return 0;
    }

    long long beg1 = beg - K;
    long long end1 = end + K;
    beg1 = max(beg1, 0LL);
    end1 = min(end1, N);

    deque<unsigned long long> d(end1 - beg1);
    for (long long i = beg1; i < end1; ++i) {
        long long v = Identifier(i);
        d[i - beg1] = v;
    }

    sort(d.begin(), d.end());

    unsigned long long res = 0;
    for (unsigned long long i = beg; i < end; ++i) {
        res += d[i - beg1] * i;
        res %= 0x100000ULL;
    }
    PutLL(MASTER_NODE, res);
    Send(MASTER_NODE);


    if (nid == MASTER_NODE) {
        long long res = 0;
        for (int node = 0; node < nodes; ++node) {
            Receive(node);
            long long r = GetLL(node);
            res += r;
            res %= 0x100000ULL;
        }
        printf("%lld\n", res);
    }

    return 0;
}