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
#include "query_of_death.h"
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

        return NORMAL_MODE;
    }
#define IS_FIRST_NODE (NID == 0)
#define IS_LAST_NODE (NID == NODES - 1)
#endif
}


int main() {
    switch (init()) {
    case SMALL_DATA__MASTER_NODE: {
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }

    deque<int> d(WORK_FOR_THIS_NODE);
    long long local_result = 0;
    bool opps = false;
    long long where_opps;
    for (long long i = BEG, j = 0; i < END; ++i) {
        int v = GetValue(i);
        d[i - BEG] = v;
        local_result += v;
        if (++j % (NODES - 1) == 0) {
            for (int k = 0; k < 50; ++k) {
                v = GetValue(i);
                if (v != d[i - BEG]) {
                    opps = true;
                    where_opps = i;
                    break;
                }
            }
        }
        if (opps) {
            break;
        }
    }
    if (!opps && WORK_FOR_THIS_NODE) {
        for (int k = 0; k < 50; ++k) {
            int v = GetValue(END - 1);
            if (v != d[END - 1 - BEG]) {
                opps = true;
                where_opps = END - 1;
                break;
            }
        }
    }

    if (opps) {
        PutLL(MASTER_NODE, -1);
        PutLL(MASTER_NODE, where_opps);
    }
    else {
        PutLL(MASTER_NODE, 1);
        PutLL(MASTER_NODE, local_result);
    }
    Send(MASTER_NODE);


    long long global_result = 0;
    if (NID == MASTER_NODE) {
        long long opps_who = -1;
        long long opps_where = -1;
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            long long stat = GetLL(node);
            if (stat == -1) {
                opps_who = node;
                opps_where = GetLL(node);
            }
            else {
                global_result += GetLL(node);
            }
        }

        for (int node = 0; node < NODES; ++node) {
            PutLL(node, opps_who);
            PutLL(node, opps_where);
            Send(node);
        }
    }

    if (opps) {
        Receive(MASTER_NODE);
        GetLL(MASTER_NODE);
        GetLL(MASTER_NODE);
        PutLL(MASTER_NODE, 0LL);
        Send(MASTER_NODE);
    }
    else {
        Receive(MASTER_NODE);
        long long opps_who = GetLL(MASTER_NODE);
        long long opps_where = GetLL(MASTER_NODE);
        long long slice = (NODES + NID - opps_who) % NODES - 1;
        long long work = (opps_who >= N % NODES ? MIN_WORK_PER_NODE : MAX_WORK_PER_NODE);
        long long beg = MIN_WORK_PER_NODE * opps_who + min<long long>(N % NODES, opps_who);
        long long end = beg + work;
        if (end > N)
            end = N;
        long long danger_ind =
            opps_where + slice - (opps_where - beg) % (NODES - 1);

        long long local_result = 0;
        for (long long i = beg + slice, j = 0; i < end; i += (NODES - 1)) {
            if (i != danger_ind) {
                local_result += GetValue(i);
            }
        }
        if (danger_ind >= beg && danger_ind < end)
            local_result += GetValue(danger_ind);
        PutLL(MASTER_NODE, local_result);
        Send(MASTER_NODE);
    }


    if (NID == MASTER_NODE) {
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            global_result += GetLL(node);
        }
        printf("%lld\n", global_result);
    }
    return 0;
}