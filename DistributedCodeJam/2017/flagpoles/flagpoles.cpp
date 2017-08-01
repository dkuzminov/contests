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
#include "flagpoles.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N = GetNumFlagpoles();

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

        if (N > 3 * NODES)
            return NORMAL_MODE;
        if (NID == 0)
            return SMALL_DATA__MASTER_NODE;
        return SMALL_DATA__OTHER_NODES;
    }
#define IS_FIRST_NODE (NID == 0)
#define IS_LAST_NODE (NID == NODES - 1)
#endif
}


int main() {
    switch (init()) {
    case SMALL_DATA__MASTER_NODE: {
        if (N < 3) {
            printf("%lld\n", N);
            return 0;
        }
        long long result = 2;
        long long span = 2;
        long long d = GetHeight(1) - GetHeight(0);
        for (long long i = 2; i < N; ++i) {
            long long d_ = GetHeight(i) - GetHeight(i - 1);
            if (d_ == d) {
                ++span;
                result = max(span, result);
            }
            else {
                d = d_;
                span = 2;
            }
        }

        printf("%lld\n", result);
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }

    PutLL(MASTER_NODE, WORK_FOR_THIS_NODE);
    if (BEG >= 1) {
        long long prev = GetHeight(BEG - 1);
        long long curr = GetHeight(BEG);

        long long d = curr - prev;
        long long left = 1;

        prev = curr;
        for (long long i = BEG + 1; i < END; ++i) {
            curr = GetHeight(i);
            long long d_ = curr - prev;
            if (d_ == d) {
                ++left;
            }
            else {
                break;
            }
            prev = curr;
        }
        PutLL(MASTER_NODE, left);
    }
    else {
        PutLL(MASTER_NODE, -1);
    }

    long long span = 2;
    long long best = 2;
    long long prev = GetHeight(BEG + 1);
    long long d = prev - GetHeight(BEG);
    for (long long i = BEG + 2; i < END; ++i) {
        long long curr = GetHeight(i);
        long long d_ = curr - prev;
        if (d_ == d) {
            ++span;
            best = max(span, best);
        }
        else {
            d = d_;
            span = 2;
        }
        prev = curr;
    }
    PutLL(MASTER_NODE, best);

    if (END < N) {
        long long prev = GetHeight(END);
        long long curr = GetHeight(END - 1);

        long long d = curr - prev;
        long long right = 1;

        prev = curr;
        for (long long i = END - 2; i >= BEG; --i) {
            curr = GetHeight(i);
            long long d_ = curr - prev;
            if (d_ == d) {
                ++right;
            }
            else {
                break;
            }
            prev = curr;
        }
        PutLL(MASTER_NODE, right);
    }
    else {
        PutLL(MASTER_NODE, -1);
    }

    Send(MASTER_NODE);



    if (NID == MASTER_NODE) {
        // Sum the results
        long long result = 0;
        long long prev = 0;
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            long long work = GetLL(node);
            long long left = GetLL(node);
            if (left != -1) {
                prev += left;
                result = max(result, prev);
            }
            long long best = GetLL(node);
            result = max(result, best);
            long long right = GetLL(node);
            if (right != -1) {
                if (work != left) {
                    prev = right;
                }
            }
            else {
                prev = 0;
            }
        }
        printf("%lld\n", result);
    }

    return 0;
}