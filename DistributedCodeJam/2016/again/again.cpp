#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include "again.h"
using namespace std;

static long LARGE_PRIME = 1000000007LL;

#define MASTER_NODE 0

int main() {
    int nodes = NumberOfNodes();
    int nid = MyNodeId();

    long long N = GetN();
    long sumA = 0;
    long sumB = 0;
    for (long long i = nid; i < N; i += nodes) {
        sumA = (sumA + GetA(i)) % LARGE_PRIME;
        sumB = (sumB + GetB(i)) % LARGE_PRIME;
    }

    PutLL(MASTER_NODE, sumA);
    PutLL(MASTER_NODE, sumB);
    Send(MASTER_NODE);

    if (nid == MASTER_NODE) {
        vector<long> partialA(nodes);
        vector<long> partialB(nodes);
        long long totalSumA = 0;
        long long totalSumB = 0;
        for (int n = 0; n < nodes; ++n) {
            Receive(n);
            partialA[n] = GetLL(n);
            partialB[n] = GetLL(n);
            totalSumA = (totalSumA + partialA[n]) % LARGE_PRIME;
            totalSumB = (totalSumB + partialB[n]) % LARGE_PRIME;
        }
        long result = (totalSumA * (long long)totalSumB) % LARGE_PRIME;
        for (int i = 0; i < nodes; ++i) {
            result = (LARGE_PRIME + result - (partialA[i] * (long long) partialB[(nodes - i) % nodes]) % LARGE_PRIME) % LARGE_PRIME;
        }

        printf("%ld\n", result);
    }

    return 0;
}