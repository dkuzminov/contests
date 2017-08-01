#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "gold.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N_ = NumberOfNuggets();
long long R = RoadLength();

namespace {
#if 1
    // Divide almost evenly
    long long MIN_WORK_PER_NODE;
    long long MAX_WORK_PER_NODE;
    long long WORK_FOR_THIS_NODE;

    long long BEG, END;
    enum { NORMAL_MODE, SMALL_DATA__MASTER_NODE, SMALL_DATA__OTHER_NODES };
    int init() {
        MIN_WORK_PER_NODE = R / NODES;
        MAX_WORK_PER_NODE = MIN_WORK_PER_NODE + (R % NODES ? 1 : 0);
        WORK_FOR_THIS_NODE = (NID >= R % NODES ? MIN_WORK_PER_NODE : MAX_WORK_PER_NODE);

        BEG = MIN_WORK_PER_NODE * NID + min<long long>(R % NODES, NID);
        END = BEG + WORK_FOR_THIS_NODE;
        if (END > R)
            END = R;

        if (R > NODES)
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
        long long result = 0;
        for (long long i = 0; i < R; ++i) {
            char c = Search(i);
            if (c == 'X')
                result ^= i;
        }

        printf("%lld\n", result);
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }


    if (NID == MASTER_NODE) {
        const long long step = 1000000000LL;
        vector<pair<long long, long long>> tasks;
        for (long long i = 0; i < R; i += step) {
            tasks.push_back(make_pair(i, min(i + step - 1, R - 1)));
        }

        long long tasks_size = tasks.size();

        for (int node = 1; node < NODES; ++node) {
            if (tasks.size()) {
                auto p = tasks.back();
                tasks.pop_back();
                PutLL(node, 1);
                PutLL(node, p.first);
                PutLL(node, p.second);
            }
            else {
                PutLL(node, -1);
            }
            Send(node);
        }

        long long result = 0;
        while (tasks_size--) {
            int node = Receive(-1);
            result ^= GetLL(node);
            if (tasks.size()) {
                auto p = tasks.back();
                tasks.pop_back();
                PutLL(node, 1);
                PutLL(node, p.first);
                PutLL(node, p.second);
            }
            else
                PutLL(node, -1);
            Send(node);
        }

        printf("%lld\n", result);
    }
    else {
        Receive(MASTER_NODE);
        long long stat = GetLL(MASTER_NODE);
        while (stat != -1) {
            long long beg = GetLL(MASTER_NODE);
            long long end = GetLL(MASTER_NODE);

            long long local_result = 0;
            stack<tuple<long long, long long, bool, char>> s;
            s.push(make_tuple(beg, end, true, Search(beg)));
            while (!s.empty()) {
                auto p = s.top();
                s.pop();
                if (get<1>(p) -get<0>(p) < 10) {
                    for (long long i = get<0>(p) +1; i < get<1>(p); ++i) {
                        char c = Search(i);
                        if (c == 'X') {
                            local_result ^= i;
                        }
                    }
                    if (get<2>(p)) {
                        if (get<3>(p) == 'X') {
                            local_result ^= get<0>(p);
                        }
                        if (get<1>(p) != get<0>(p)) {
                            char c = Search(get<1>(p));
                            if (c == 'X') {
                                local_result ^= get<1>(p);
                            }
                        }
                    }
                    else {
                        if (get<3>(p) == 'X') {
                            local_result ^= get<1>(p);
                        }
                        if (get<1>(p) != get<0>(p)) {
                            char c = Search(get<0>(p));
                            if (c == 'X') {
                                local_result ^= get<0>(p);
                            }
                        }
                    }
                }
                else {
                    switch (get<3>(p)) {
                    case 'X':
                        local_result ^= get<2>(p) ? get<0>(p) : get<1>(p);
                    case '=':
                        s.push(make_tuple(get<2>(p) ? get<0>(p) +1 : get<0>(p),
                            get<2>(p) ? get<1>(p) : get<1>(p) -1,
                            get<2>(p),
                            Search(get<2>(p) ? get<0>(p) +1 : get<1>(p) -1)));
                        break;
                    case '>':
                        if (get<2>(p)) {
                            long long mid = (get<1>(p) -get<0>(p) +1) / 2 + get<0>(p);
                            char c = Search(mid);
                            s.push(make_tuple(mid, get<1>(p), true, c));
                            if (c == 'X') {
                                --mid;
                                c = Search(mid);
                            }
                            s.push(make_tuple(get<0>(p) +1, mid, false, c));
                        }
                        else {
                            long long step = 2;
                            long long ind = get<1>(p);
                            for (;; step *= 2) {
                                ind -= step;
                                if (ind < get<0>(p))
                                    break;
                                char c = Search(ind);
                                if (c != '>') {
                                    s.push(make_tuple(get<0>(p), ind, false, c));
                                    break;
                                }
                            }
                        }
                        break;
                    case '<':
                    default:
                        if (get<2>(p)) {
                            long long step = 2;
                            long long ind = get<0>(p);
                            for (;; step *= 2) {
                                ind += step;
                                if (ind > get<1>(p))
                                    break;
                                char c = Search(ind);
                                if (c != '<') {
                                    s.push(make_tuple(ind, get<1>(p), true, c));
                                    break;
                                }
                            }
                        }
                        else {
                            long long mid = (get<1>(p) -get<0>(p) +1) / 2 + get<0>(p);
                            char c = Search(mid);
                            s.push(make_tuple(mid, get<1>(p) -1, true, c));
                            if (c == 'X') {
                                --mid;
                                c = Search(mid);
                            }
                            s.push(make_tuple(get<0>(p), mid, false, c));
                        }
                    }
                }
            }

            PutLL(MASTER_NODE, local_result);
            Send(MASTER_NODE);

            Receive(MASTER_NODE);
            stat = GetLL(MASTER_NODE);
        }
    }

    return 0;
}