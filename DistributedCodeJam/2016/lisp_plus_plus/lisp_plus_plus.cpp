#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <string>
#include <unordered_map>
#include "lisp_plus_plus.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N = GetLength();

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
        long long result = -1;
        long long counter = 0;
        for (long long i = 0; i < N; ++i) {
            char c = GetCharacter(i);
            counter += (c == '(' ? 1 : -1);
            if (counter < 0) {
                result = i;
                break;
            }
        }
        if (counter == 0)
            result = -1;
        else if (counter > 0)
            result = N;

        printf("%lld\n", result);
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }
    // ############################################

    long long local_counter = 0;
    long long local_worst = N;
    for (long long i = BEG; i < END; ++i) {
        char c = GetCharacter(i);
        local_counter += (c == '(' ? 1 : -1);
        local_worst = min(local_worst, local_counter);
    }

    long long prev = 0;
    if (NID != 0) {
        Receive(NID - 1);
        long long action = GetLL(NID - 1);
        if (action == -1) {
            if (!IS_LAST_NODE) {
                PutLL(NID + 1, -1);
                Send(NID + 1);
            }
            return 0;
        }
        prev = GetLL(NID - 1);
        local_counter += prev;
        local_worst += prev;
    }

    if (local_worst < 0) {
        if (!IS_LAST_NODE) {
            PutLL(NID + 1, -1);
            Send(NID + 1);
        }
        long long counter = prev;
        long long result;
        for (long long i = BEG; i < END; ++i) {
            char c = GetCharacter(i);
            counter += (c == '(' ? 1 : -1);
            if (counter < 0) {
                result = i;
                break;
            }
        }

        PutLL(MASTER_NODE, result);
        Send(MASTER_NODE);

    }
    else {
        if (!IS_LAST_NODE) {
            PutLL(NID + 1, 1);
            PutLL(NID + 1, local_counter);
            Send(NID + 1);
        }
        else {
            if (local_counter == 0) {
                PutLL(MASTER_NODE, -1);
                Send(MASTER_NODE);
            }
            else {
                PutLL(MASTER_NODE, N);
                Send(MASTER_NODE);
            }
        }
    }

    if (NID == MASTER_NODE) {
        int node = Receive(-1);
        long long result = GetLL(node);
        printf("%lld\n", result);
    }
    return 0;
}