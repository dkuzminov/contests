#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include "gas_stations.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N = GetNumKms();
long long K = GetTankSize();

#if 0
    // Divide almost evenly
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


int main() {
    switch (init()) {
    case SMALL_DATA__MASTER_NODE: {
        long long result = 0;
        deque<pair<long long, long>> q;
        for (long long i = 0; i < N; ++i) {
            long long p = GetGasPrice(i);
            if (!q.empty() && q.front().second + K <= i)
                q.pop_front();
            while (!q.empty() && q.back().first > p)
                q.pop_back();
            q.push_back(make_pair(p, i));
            result += q.front().first;
        }
        printf("%lld\n", result);
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }

    if (K - 1 < 2 * work_per_node) {
        long long local_result = 0;
        deque<pair<long long, long>> q;
        for (long long i = max(0LL, BEG - K + 1); i < END; ++i) {
            long long p = GetGasPrice(i);
            if (!q.empty() && q.front().second + K <= i)
                q.pop_front();
            while (!q.empty() && q.back().first > p)
                q.pop_back();
            q.push_back(make_pair(p, i));
            if (i >= BEG)
                local_result += q.front().first;
        }
        PutLL(MASTER_NODE, local_result);
        Send(MASTER_NODE);
    }
    else {
        long long min_price = GetGasPrice(BEG);
        for (long long i = BEG + 1; i < END; ++i) {
            long long p = GetGasPrice(i);
            min_price = min(min_price, p);
        }
        for (int n = NID + 1; n < NODES; ++n) {
            PutLL(n, min_price);
            Send(n);
        }

        long long best_default_price = 10000000000LL;
        int full_prev_ranges = (K - 1) / work_per_node - 1;
        if (!IS_FIRST_NODE) {
            for (int n = max(0, NID - full_prev_ranges); n < NID; ++n) {
                Receive(n);
                best_default_price = min(best_default_price, GetLL(n));
            }
        }
        deque<pair<long long, long>> q;
        for (long long i = max(0LL, BEG - K + 1); i < max(0LL, BEG - work_per_node * full_prev_ranges); ++i) {
            long long p = GetGasPrice(i);
            while (!q.empty() && q.back().first > p)
                q.pop_back();
            q.push_back(make_pair(p, i));
        }
        while (!q.empty() && q.back().first > best_default_price)
            q.pop_back();
        q.push_back(make_pair(best_default_price, BEG - 1));

        long long local_result = 0;
        for (long long i = BEG; i < END; ++i) {
            long long p = GetGasPrice(i);
            if (!q.empty() && q.front().second + K <= i)
                q.pop_front();
            while (!q.empty() && q.back().first > p)
                q.pop_back();
            q.push_back(make_pair(p, i));
            local_result += q.front().first;
        }
        PutLL(MASTER_NODE, local_result);
        Send(MASTER_NODE);
    }


    if (NID == MASTER_NODE) {
        long long result = 0;
        for (int n = 0; n < NODES; ++n) {
            Receive(n);
            result += GetLL(n);
        }
        printf("%lld\n", result);
    }

    return 0;
}
