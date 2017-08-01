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
#include "broken_memory.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N = GetLength();

void proceed(long long chunk_size, long long base_ind, deque<long long> &local_data, long long profile[10]) {
    for (int k = 0; k < 10; ++k) {
        long long beg = base_ind + k * chunk_size;
        long long end = min(beg + chunk_size, N);
        if (beg == end) {
            profile[k] = 0;
            continue;
        }

        string tmp;
        for (long long i = beg; i < end; ++i) {
            long long t = local_data[i];
            for (int j = 0; j < 8; ++j) {
                tmp.push_back(t & 0xFF);
                t >>= 8;
            }
        }
        std::hash<string> h;
        long long hash = std::hash<string>()(tmp);
        profile[k] = hash;
    }
}



int main() {
    deque<long long> local_data(N);
    for (long long i = 0; i < N; ++i) {
        local_data[i] = GetValue(i);
    }

    long long chunk_size = 10000000LL;
    long base_ind = 0;
    do {
        chunk_size /= 10;
        if (chunk_size >= N)
            continue;

        // <-- request -->
        PutLL((NODES + NID - 1) % NODES, base_ind);
        PutLL((NODES + NID + 1) % NODES, base_ind);
        Send((NODES + NID - 1) % NODES);
        Send((NODES + NID + 1) % NODES);

        long long left[10];
        long long self[10];
        long long right[10];

        proceed(chunk_size, base_ind, local_data, self);

        // <-- provide data
        Receive((NODES + NID - 1) % NODES);
        long long left_base_index = GetLL((NODES + NID - 1) % NODES);
        proceed(chunk_size, left_base_index, local_data, left);
        for (int k = 0; k < 10; ++k) {
            PutLL((NODES + NID - 1) % NODES, left[k]);
        }
        Send((NODES + NID - 1) % NODES);

        // provide data -->
        Receive((NODES + NID + 1) % NODES);
        long long right_base_index = GetLL((NODES + NID + 1) % NODES);
        proceed(chunk_size, right_base_index, local_data, right);
        for (int k = 0; k < 10; ++k) {
            PutLL((NODES + NID + 1) % NODES, right[k]);
        }
        Send((NODES + NID + 1) % NODES);

        // --> receive data <--
        Receive((NODES + NID - 1) % NODES);
        Receive((NODES + NID + 1) % NODES);
        for (int k = 0; k < 10; ++k) {
            left[k] = GetLL((NODES + NID - 1) % NODES);
            right[k] = GetLL((NODES + NID + 1) % NODES);
        }

        int A = -1;
        int S = -1;
        int L = -1;
        int R = -1;
        for (int k = 0; k < 10; ++k) {
            if (left[k] == right[k] && left[k] != self[k]) {
                S = k;
            }
            else if (left[k] != self[k] && self[k] == right[k]) {
                L = k;
            }
            else if (left[k] == self[k] && self[k] != right[k]) {
                R = k;
            }
            else if (left[k] != right[k] && left[k] != self[k] && self[k] != right[k]) {
                A = k;
            }
        }
        int K = -1;
        if (S != -1)
            K = S;
        else
            K = A;

        base_ind += K * chunk_size;
    } while (chunk_size > 1);

    PutLL(MASTER_NODE, base_ind);
    Send(MASTER_NODE);

    if (NID == MASTER_NODE) {
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            long long res = GetLL(node);
            printf("%lld ", res);
        }
        printf("\n");
    }
    return 0;
}