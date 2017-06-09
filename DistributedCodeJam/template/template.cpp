#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "template.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N = GetN___________________________________();

namespace {
#if 1
    // Divide almost evenly
    long long MIN_WORK_PER_NODE;
    long long MAX_WORK_PER_NODE;
    long long WORK_FOR_THIS_NODE;

    long long BEG, END;
    enum { NORMAL_MODE, SMALL_DATA__MASTER_NODE, SMALL_DATA__OTHER_NODES };
    int init() {
        MIN_WORK_PER_NODE = N / NODES;
        MAX_WORK_PER_NODE = MIN_WORK_PER_NODE + (N % NODES ? 1 : 0);
        WORK_FOR_THIS_NODE = (NID >= N % NODES ? MIN_WORK_PER_NODE : MAX_WORK_PER_NODE);

        BEG = MIN_WORK_PER_NODE * NID + min<long long>(N % NODES, NID);
        END = BEG + WORK_FOR_THIS_NODE;
        if (END > N)
            END = N;

        if (N > NODES)
            return NORMAL_MODE;
        if (NID == 0)
            return SMALL_DATA__MASTER_NODE;
        return SMALL_DATA__OTHER_NODES;
    }
#define IS_FIRST_NODE (NID == 0)
#define IS_LAST_NODE (NID == NODES - 1)
#elif 1
    // Divide on equal ranges (except of the last one)
    long long work_per_node;
    long long BEG, END;
    enum { NORMAL_MODE, SMALL_DATA__MASTER_NODE, SMALL_DATA__OTHER_NODES };
    int init() {
        work_per_node = N / NODES + (N % NODES ? 1 : 0);
        BEG = work_per_node * NID;
        END = work_per_node * (NID + 1);
        if (END > N)
            END = N;

        if (N > NODES)
            return NORMAL_MODE;
        if (NID == 0)
            return SMALL_DATA__MASTER_NODE;
        return SMALL_DATA__OTHER_NODES;
    }
#define IS_FIRST_NODE (NID == 0)
#define IS_LAST_NODE (NID == NODES - 1)
#elif 1
#endif
}


int main() {
    switch (init()) {
    case SMALL_DATA__MASTER_NODE: {

        printf("%lld\n", ____________);
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }


    if (NID == MASTER_NODE) {
        // Sum the results
        long long result = 0;
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            result += GetLL(node);
        }
        printf("%lld\n", result);

        // Or receive the answer from a single node
        int node = Receive(___);
        long long result = GetLL(node);
        printf("%lld\n", result);
    }

    return 0;
}