#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <vector>
#include "crates.h"
using namespace std;

#define MASTER_NODE 0
#define is_last (nid == nodes - 1)
static long LARGE_PRIME = 1000000007LL;


int main() {
    long long nodes = NumberOfNodes();
    long long nid = MyNodeId();

    long long N = GetNumStacks();

    long long min_work_per_node = N / nodes;
    long long max_work_per_node = min_work_per_node + (N % nodes ? 1 : 0);
    long long work_per_node = (nid >= N % nodes? min_work_per_node: max_work_per_node);

    long long beg = min_work_per_node * nid + min(N % nodes, nid);
    long long end = beg + work_per_node;

    if(beg >= N || beg == end) {
        if (!is_last) {
            Receive(nid + 1);
            GetLL(nid + 1);
        }
        PutLL(nid - 1, -1);
        Send(nid - 1);
        Receive(nid - 1);
        GetLL(nid - 1);
        if (!is_last) {
            PutLL(nid + 1, 0);
            Send(nid + 1);
        }
        PutLL(MASTER_NODE, 0);
	    Send(MASTER_NODE);
    }
    else {
        long long own_sum = 0;
        for (long long i = beg; i < end; ++i) {
            long long v = GetStackHeight(i + 1);
            own_sum += v;
        }

        long long sum_to_the_right = 0;
        if (is_last) {
            sum_to_the_right = 0;
        }
        else {
            Receive(nid + 1);
            sum_to_the_right = GetLL(nid + 1);
            if (sum_to_the_right == -1) {
                sum_to_the_right = 0;
            }
        }

        long long total_from_here = own_sum + sum_to_the_right;
        long long h;
        long long top_run;
        long long need_here;
        long long surplus_from_left;
        long long surplus_to_right;
        if (nid != 0) {
            PutLL(nid - 1, total_from_here);
            Send(nid - 1);
            // Waiting for the previous node
            Receive(nid - 1);
            h = GetLL(nid - 1);
            top_run = GetLL(nid - 1);
            surplus_from_left = GetLL(nid - 1);
            need_here = h * (end - beg) + min<long long>(top_run, (end - beg));
            surplus_to_right = own_sum + surplus_from_left - need_here;
            if (!is_last) {
                PutLL(nid + 1, h);
                PutLL(nid + 1, max<long long>(top_run - (end - beg), 0));
                PutLL(nid + 1, surplus_to_right);
                Send(nid + 1);
            }
        }
        else {
            h = total_from_here / N;
            top_run = total_from_here % N;
            need_here = h * (end - beg) + min<long long>(top_run, (end - beg));
            surplus_from_left = 0;
            surplus_to_right = own_sum - need_here;
            PutLL(/*nid + */1, h);
            PutLL(/*nid + */1, max<long long>(top_run - (end - beg), 0LL));
            PutLL(/*nid + */1, surplus_to_right);
            Send(/*nid + */1);
        }

        long long moves = 0;
        long long d = GetStackHeight(beg + 1) + surplus_from_left;
        for (long long i = beg; i < end - 1; ++i) {
            long long d_next = GetStackHeight(i + 2);
            long long goal = h + ((i - beg) < top_run? 1: 0);
            moves += abs(d - goal);
            moves %= LARGE_PRIME;
            d_next += d - goal;
            d = d_next;
        }
        moves += abs(surplus_to_right);
        moves %= LARGE_PRIME;

        PutLL(MASTER_NODE, moves);
        Send(MASTER_NODE);

        if (nid == MASTER_NODE) {
            long long total_moves = 0;
            for (int node = 0; node < nodes; ++node) {
                Receive(node);
                total_moves += GetLL(node);
                total_moves %= LARGE_PRIME;
            }
            printf("%lld\n", total_moves);
        }
    }

    return 0;
}