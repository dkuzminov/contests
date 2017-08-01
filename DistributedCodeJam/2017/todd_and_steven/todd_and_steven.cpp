#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <map>
#include "todd_and_steven.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N = GetToddLength() + GetStevenLength();
long long T = GetToddLength();
long long S = GetStevenLength();

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

int main() {
    switch (init()) {
    case SMALL_DATA__MASTER_NODE: {
        vector<long long> td(T);
        vector<long long> st(S);
        for (long long i = 0; i < T; ++i) {
            td[i] = GetToddValue(i);
        }
        for (long long j = 0; j < S; ++j) {
            st[j] = GetStevenValue(j);
        }

        long long res = 0;
        for (long long I = 0, i = 0, j = 0; i < T || j < S; ++I) {
            if (i == T) {
                long long tmp = I ^ st[j];
                res += tmp;
                ++j;
            }
            else if (j == S) {
                long long tmp = I ^ td[i];
                res += tmp;
                ++i;
            }
            else {
                long long tmp;
                if (td[i] < st[j])
                    tmp = I ^ td[i++];
                else
                    tmp = I ^ st[j++];
                res += tmp;
            }
            res %= 1000000007LL;
        }

        printf("%lld\n", res);
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }
    // ############################################

    long long i = min(T - 1, BEG);
    long long j = BEG - i;

    long long step = i;
    while (1) {
        step /= 2;
        if (step == 0)
            step = 1;

        if (i == 0 && j == 0)
            break;
        if (i == T || j == S)
            break;

        long long td = GetToddValue(i);
        long long st = GetStevenValue(j);
        if (i == 0) {
            if (st < td)
                break;
            if (td > GetStevenValue(j - 1))
                break;
            step = min(step, min(j, max(T - i - 1, 1LL)));
            i += step;
            j -= step;
        }
        else if (j == 0) {
            if (td < st)
                break;
            if (st > GetToddValue(i - 1))
                break;
            step = min(step, min(i, max(S - j - 1, 1LL)));
            i -= step;
            j += step;
        }
        else if (st < td) {
            if (st > GetToddValue(i - 1))
                break;
            step = min(step, min(i, max(S - j - 1, 1LL)));
            i -= step;
            j += step;
        }
        else {
            if (td > GetStevenValue(j - 1))
                break;
            step = min(step, min(j, max(T - i - 1, 1LL)));
            i += step;
            j -= step;
        }
    }

    long long local_res = 0;
    long long td = (i < T? GetToddValue(i): 0);
    long long st = (j < S? GetStevenValue(j): 0);
    for (long long I = BEG; I < END; ++I) {
        if (i == T) {
            long long tmp = I ^ st;
            local_res += tmp;
            ++j;
            st = (j < S ? GetStevenValue(j) : 0);
        }
        else if (j == S) {
            long long tmp = I ^ td;
            local_res += tmp;
            ++i;
            td = (i < T ? GetToddValue(i) : 0);
        }
        else {
            long long tmp;
            if (td < st) {
                tmp = I ^ td;
                ++i;
                td = (i < T? GetToddValue(i): 0);
            }
            else {
                tmp = I ^ st;
                ++j;
                st = (j < S? GetStevenValue(j): 0);
            }
            local_res += tmp;
        }
        local_res %= 1000000007LL;
    }

    PutLL(MASTER_NODE, local_res);
    Send(MASTER_NODE);


    if (NID == MASTER_NODE) {
        long long res = 0;
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            res += GetLL(node);
            res %= 1000000007LL;
        }
        printf("%lld\n", res);
    }

    return 0;
}