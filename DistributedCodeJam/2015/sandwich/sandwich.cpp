#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include "sandwich.h"
using namespace std;

#define MASTER_NODE 0

int main() {
    int nodes = NumberOfNodes();
    int id = MyNodeId();

    long long N = GetN();
    long long work_per_node = N / nodes + (N % nodes ? 1 : 0);
    long long beg = work_per_node * id;
    long long end = work_per_node * (id + 1);
    if (end > N)
        end = N;

    if (work_per_node == 1) {
        nodes = N;
        if (id >= nodes)
            return 0;
        if (N == 1) {
            printf("%lld\n", max(0LL, GetTaste(0)));
            return 0;
        }
    }


    long long own_sum = 0;
    deque<long long> d(end - beg);
    for (long long i = beg; i < end; ++i) {
        long long t = GetTaste(i);
        d[i - beg] = t;
        own_sum += t;
    }

    long long sum_right;
    long long sum_left;
    if (id == nodes - 1) {
        sum_right = 0;
        PutLL(id - 1, own_sum);
        Send(id - 1);
    }
    else {
        Receive(id + 1);
        sum_right = GetLL(id + 1);
        if (id != 0) {
            PutLL(id - 1, own_sum + sum_right);
            Send(id - 1);
        }
    }

    if (id == 0) {
        sum_left = 0;
        PutLL(id + 1, own_sum);
        Send(id + 1);
    }
    else {
        Receive(id - 1);
        sum_left = GetLL(id - 1);
        if (id != nodes - 1) {
            PutLL(id + 1, own_sum + sum_left);
            Send(id + 1);
        }
    }

    long long neg_sum = 0;
    long long sum = 0;
    for (long long i = beg; i < end; ++i) {
        long long t = d[i - beg];
        sum += t;
        if (sum > 0) {
            sum = 0;
        }
        neg_sum = min(neg_sum, sum);
    }

    long long rec_left = sum_left;
    sum = sum_left;
    for (long long i = beg; i < end; ++i) {
        sum += d[i - beg];
        rec_left = max(rec_left, sum);
    }
    long long rec_right = sum_right;
    sum = sum_right;
    for (long long i = end - 1; i >= beg; --i) {
        sum += d[i - beg];
        rec_right = max(rec_right, sum);
    }

    if (sum_left + own_sum - neg_sum + sum_right > 0) {
        PutLL(MASTER_NODE, sum_left + own_sum - neg_sum + sum_right);
    }
    else {
        PutLL(MASTER_NODE, 0);
    }

    if (rec_left >= 0) {
        PutLL(MASTER_NODE, rec_left);
    }
    else {
        PutLL(MASTER_NODE, 0);
    }

    if (rec_right >= 0) {
        PutLL(MASTER_NODE, rec_right);
    }
    else {
        PutLL(MASTER_NODE, 0);
    }
    Send(MASTER_NODE);


    if (id == MASTER_NODE) {
        deque<long long> full(nodes);
        deque<long long> left(nodes);
        deque<long long> right(nodes);
        long long best = 0;
        for (int node = 0; node < nodes; ++node) {
            Receive(node);
            long long r = GetLL(node);
            full[node] = r;
            r = GetLL(node);
            left[node] = r;
            r = GetLL(node);
            right[node] = r;
            best = max(best, full[node]);
        }

        long long best_left = 0;
        for (int node = 0; node < nodes; ++node) {
            best = max(best, best_left + right[node]);
            best_left = max(best_left, left[node]);
        }

        printf("%lld\n", best);
    }

    return 0;
}