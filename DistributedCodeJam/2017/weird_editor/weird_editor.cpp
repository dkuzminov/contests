#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <map>
#include "weird_editor.h"
using namespace std;

#define MASTER_NODE 0

int main() {
    int nodes = NumberOfNodes();
    int nid = MyNodeId();

    long long N = GetNumberLength();
    long long min_work_per_node = N / nodes;
    long long max_work_per_node = min_work_per_node + (N % nodes ? 1 : 0);
    long long work_per_node = (nid >= N % nodes ? min_work_per_node : max_work_per_node);

    long long beg = min_work_per_node * nid + min<long long>(N % nodes, nid);
    long long end = beg + work_per_node;

    if (beg >= N || beg == end) {
        for (int d = 9; d > 0; --d) {
            PutLL(MASTER_NODE, 0LL);
        }
        Send(MASTER_NODE);

        Receive(MASTER_NODE);
        for (int d = 0; d <= 9; ++d) {
            GetLL(MASTER_NODE);
        }

        PutLL(MASTER_NODE, 0LL);
        Send(MASTER_NODE);
        return 0;
    }


    long long local_counts[10] = {0,0,0,0,0,0,0,0,0,0};
    long long local_curr = 9;
    for (long long i = beg; i < end; ++i) {
        long long d = GetDigit(i);
        if (d > local_curr) {
            for (int _d = 0; _d < d; ++_d) {
                local_counts[_d] = 0;
            }
        }
        ++local_counts[d];
        local_curr = d;
    }

    for (int d = 9; d > 0; --d) {
        PutLL(MASTER_NODE, local_counts[d]);
    }
    Send(MASTER_NODE);


    if (nid == MASTER_NODE) {
        long long total_counts[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        for (int node = 0; node < nodes; ++node) {
            Receive(node);
            for (int d = 9; d > 0; --d) {
                long long cnt = GetLL(node);
                if (cnt > 0) {
                    for (int _d = 0; _d < d; ++_d) {
                        total_counts[_d] = 0;
                    }
                    total_counts[d] += cnt;
                }
            }
        }

        long long zeroes = N;
        for (int d = 1; d <= 9; ++d) {
            if (total_counts[d] != 0)
                zeroes -= total_counts[d];
        }
        total_counts[0] = zeroes;


        long long beg = 0;
        for (int node = 0; node < nodes; ++node) {
            long long wpn = max_work_per_node;
            long long local_counts[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            for (int d = 0; d <= 9; ++d) {
                local_counts[d] = min(total_counts[d], wpn);
                total_counts[d] -= local_counts[d];
                wpn -= local_counts[d];
            }
            for (int d = 0; d <= 9; ++d) {
                PutLL(node, local_counts[d]);
            }
            Send(node);
        }
    }

    long long local_res = 0;
    {
        long long local_counts[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Receive(MASTER_NODE);
        for (int d = 0; d <= 9; ++d) {
            local_counts[d] = GetLL(MASTER_NODE);
        }
        for (int d = 9; d >= 0; --d) {
            while (local_counts[d]) {
                local_res *= 10;
                local_res += d;
                local_res %= 1000000007LL;
                --local_counts[d];
            }
        }
        PutLL(MASTER_NODE, local_res);
        Send(MASTER_NODE);
    }


    if (nid == MASTER_NODE) {
        long long wpn = max_work_per_node;
        long long power = 1;
        while (wpn) {
            power *= 10;
            power %= 1000000007LL;
            --wpn;
        }

        long long res = 0;

        for (int node = nodes - 1; node >= 0; --node) {
            res *= power;
            res %= 1000000007LL;
            Receive(node);
            long long local_res = GetLL(node);
            res += local_res;
            res %= 1000000007LL;
        }

        printf("%lld\n", res);
    }

    return 0;
}