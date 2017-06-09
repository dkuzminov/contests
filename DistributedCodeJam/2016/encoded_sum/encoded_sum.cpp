#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <set>
#include <unordered_map>
#include "encoded_sum.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N = GetLength();
const long long MOD = 1000000007LL;

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

        BEG = MIN_WORK_PER_NODE * NID + min(N % NODES, (long long) NID);
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
    long long WORK_PER_NODE;
    long long BEG, END;
    enum { NORMAL_MODE, SMALL_DATA__MASTER_NODE, SMALL_DATA__OTHER_NODES };
    int init() {
        WORK_PER_NODE = N / NODES + (N % NODES ? 1 : 0);
        BEG = WORK_PER_NODE * NID;
        END = WORK_PER_NODE * (NID + 1);
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

void resolve(int d, vector<set<int>> &possibilities, int resolution[10]) {
    set<int> to_process = { d };
    while (!to_process.empty()) {
        int d = *to_process.begin();
        to_process.erase(d);
        for (int j = 0; j < 10; ++j) {
            if (possibilities[j].size() == 1 && resolution[j] == -1) {
                resolution[j] = *possibilities[j].begin();
                for (int k = 0; k < 10; ++k) {
                    if (k != j) {
                        possibilities[k].erase(resolution[j]);
                        if (possibilities[k].size() == 1) {
                            to_process.insert(*possibilities[k].begin());
                        }
                    }
                }
            }
        }
    }
}

int main() {
    switch (init()) {
    case SMALL_DATA__MASTER_NODE: {
        long long sub_results[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        vector<set<int>> possibilities(10, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        int resolution[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
        for (int i = 0; i < N; ++i) {
            char l1 = GetScrollOne(i);
            char l2 = GetScrollTwo(i);
            for (int j = 0; j < 10; ++j) {
                sub_results[j] *= 10;
                sub_results[j] %= MOD;
            }
            sub_results[l1 - 'A'] += 1;
            sub_results[l2 - 'A'] += 1;

            if (l1 == l2 && resolution[l1 - 'A'] == -1) {
                int d = *possibilities[l1 - 'A'].rbegin();
                possibilities[l1 - 'A'] = { d };
                resolve(d, possibilities, resolution);
            }
            else if (l1 != l2 && (resolution[l1 - 'A'] == -1 || resolution[l2 - 'A'] == -1)) {
                if (resolution[l1 - 'A'] != -1) {
                    int d = *possibilities[l2 - 'A'].rbegin();
                    possibilities[l2 - 'A'] = { d };
                    resolve(d, possibilities, resolution);
                }
                else if (resolution[l2 - 'A'] != -1) {
                    int d = *possibilities[l1 - 'A'].rbegin();
                    possibilities[l1 - 'A'] = { d };
                    resolve(d, possibilities, resolution);
                }
                else {
                    int best_d1 = *possibilities[l1 - 'A'].rbegin();
                    int subbest_d1 = *++possibilities[l1 - 'A'].rbegin();
                    int best_d2 = *possibilities[l2 - 'A'].rbegin();
                    int subbest_d2 = *++possibilities[l2 - 'A'].rbegin();
                    if (best_d1 != best_d2) {
                        possibilities[l1 - 'A'] = { best_d1 };
                        possibilities[l2 - 'A'] = { best_d2 };
                        resolve(best_d1, possibilities, resolution);
                        resolve(best_d2, possibilities, resolution);
                    }
                    else if (best_d1 + subbest_d2 < best_d2 + subbest_d1) {
                        possibilities[l1 - 'A'] = { subbest_d1 };
                        possibilities[l2 - 'A'] = { best_d2 };
                        resolve(subbest_d1, possibilities, resolution);
                        resolve(best_d2, possibilities, resolution);
                    }
                    else if (best_d1 + subbest_d2 > best_d2 + subbest_d1) {
                        possibilities[l1 - 'A'] = { best_d1 };
                        possibilities[l2 - 'A'] = { subbest_d2 };
                        resolve(best_d1, possibilities, resolution);
                        resolve(subbest_d2, possibilities, resolution);
                    }
                    else {
                        possibilities[l1 - 'A'] = { best_d1, subbest_d1 };
                        possibilities[l2 - 'A'] = { best_d2, subbest_d2 };
                        for (int j = 0; j < 10; ++j) {
                            if (j != l1 - 'A' && j != l2 - 'A') {
                                possibilities[j].erase(best_d1);
                                possibilities[j].erase(subbest_d1);
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 10; ++i) {
            if (possibilities[i].size() > 1) {
                int d = *possibilities[i].begin();
                possibilities[i] = { d };
                resolve(d, possibilities, resolution);
            }
        }

        long long result = 0;
        for (int d = 0; d < 10; ++d) {
            result += sub_results[d] * resolution[d];
            result %= MOD;
        }

        printf("%lld\n", result);
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }
    //###########################################################

    set<pair<char, char>> s;
    vector<pair<char, char>> v;
    long long sub_results[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    long long power = 1;
    for (int i = BEG; i < END; ++i) {
        char l1 = GetScrollOne(i);
        char l2 = GetScrollTwo(i);
        for (int j = 0; j < 10; ++j) {
            sub_results[j] *= 10;
            sub_results[j] %= MOD;
        }
        sub_results[l1 - 'A'] += 1;
        sub_results[l2 - 'A'] += 1;
        power = (power * 10) % MOD;
        if (l1 > l2)
            swap(l1, l2);
        pair<char, char> p {l1, l2};
        if (s.count(p) == 0) {
            s.insert(p);
            v.push_back(p);
        }
    }
    if (!IS_LAST_NODE) {
        Receive(NID + 1);
        long long p = GetLL(NID + 1);
        for (int j = 0; j < 10; ++j) {
            sub_results[j] *= p;
            sub_results[j] %= MOD;
        }
        power = (power * p) % MOD;
    }
    if (!IS_FIRST_NODE) {
        PutLL(NID - 1, power);
        Send(NID - 1);
    }
    for (int j = 0; j < 10; ++j) {
        PutLL(MASTER_NODE, sub_results[j]);
    }
    Send(MASTER_NODE);

    for (auto p : v) {
        PutChar(MASTER_NODE, p.first);
        PutChar(MASTER_NODE, p.second);
    }
    PutChar(MASTER_NODE, ' ');
    Send(MASTER_NODE);



    if (NID == MASTER_NODE) {
        long long global_sub_results[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            for (int j = 0; j < 10; ++j) {
                global_sub_results[j] += GetLL(node);
                global_sub_results[j] %= MOD;
            }
        }


        vector<set<int>> possibilities(10, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
        int resolution[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            while (1) {
                char l1 = GetChar(node);
                if (l1 == ' ')
                    break;
                char l2 = GetChar(node);
                if (l1 == l2 && resolution[l1 - 'A'] == -1) {
                    int d = *possibilities[l1 - 'A'].rbegin();
                    possibilities[l1 - 'A'] = { d };
                    resolve(d, possibilities, resolution);
                }
                else if (l1 != l2 && (resolution[l1 - 'A'] == -1 || resolution[l2 - 'A'] == -1)) {
                    if (resolution[l1 - 'A'] != -1) {
                        int d = *possibilities[l2 - 'A'].rbegin();
                        possibilities[l2 - 'A'] = { d };
                        resolve(d, possibilities, resolution);
                    }
                    else if (resolution[l2 - 'A'] != -1) {
                        int d = *possibilities[l1 - 'A'].rbegin();
                        possibilities[l1 - 'A'] = { d };
                        resolve(d, possibilities, resolution);
                    }
                    else {
                        int best_d1 = *possibilities[l1 - 'A'].rbegin();
                        int subbest_d1 = *++possibilities[l1 - 'A'].rbegin();
                        int best_d2 = *possibilities[l2 - 'A'].rbegin();
                        int subbest_d2 = *++possibilities[l2 - 'A'].rbegin();
                        if (best_d1 != best_d2) {
                            possibilities[l1 - 'A'] = { best_d1 };
                            possibilities[l2 - 'A'] = { best_d2 };
                            resolve(best_d1, possibilities, resolution);
                            resolve(best_d2, possibilities, resolution);
                        }
                        else if (best_d1 + subbest_d2 < best_d2 + subbest_d1) {
                            possibilities[l1 - 'A'] = { subbest_d1 };
                            possibilities[l2 - 'A'] = { best_d2 };
                            resolve(subbest_d1, possibilities, resolution);
                            resolve(best_d2, possibilities, resolution);
                        }
                        else if (best_d1 + subbest_d2 > best_d2 + subbest_d1) {
                            possibilities[l1 - 'A'] = { best_d1 };
                            possibilities[l2 - 'A'] = { subbest_d2 };
                            resolve(best_d1, possibilities, resolution);
                            resolve(subbest_d2, possibilities, resolution);
                        }
                        else {
                            possibilities[l1 - 'A'] = { best_d1, subbest_d1 };
                            possibilities[l2 - 'A'] = { best_d2, subbest_d2 };
                            for (int j = 0; j < 10; ++j) {
                                if (j != l1 - 'A' && j != l2 - 'A') {
                                    possibilities[j].erase(best_d1);
                                    possibilities[j].erase(subbest_d1);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 10; ++i) {
            if (possibilities[i].size() > 1) {
                int d = *possibilities[i].begin();
                possibilities[i] = { d };
                resolve(d, possibilities, resolution);
            }
        }


        long long result = 0;
        for (int j = 0; j < 10; ++j) {
            result += global_sub_results[j] * resolution[j];
            result %= MOD;
        }

        printf("%lld\n", result);
    }

    return 0;
}