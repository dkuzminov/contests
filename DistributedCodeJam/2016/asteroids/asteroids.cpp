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
#include "asteroids.h"
using namespace std;

#define MASTER_NODE 0
int NODES = NumberOfNodes();
int NID = MyNodeId();
long long H = GetHeight();
long long W = GetWidth();
long long N = GetWidth();

namespace {
#if 1
    // Divide on equal ranges (except of the last one)
    long long BASIC_WORK_PER_NODE;
    long long WORK_FOR_THIS_NODE;
    long long BEG, END;
    enum { NORMAL_MODE, SMALL_DATA__MASTER_NODE, SMALL_DATA__OTHER_NODES };
    int init() {
        BASIC_WORK_PER_NODE = N / NODES + (N % NODES ? 1 : 0);
        BEG = BASIC_WORK_PER_NODE * NID;
        END = BASIC_WORK_PER_NODE * (NID + 1);
        WORK_FOR_THIS_NODE = BASIC_WORK_PER_NODE;
        if (END > N) {
            END = N;
            WORK_FOR_THIS_NODE = END - BEG;
        }

        if (N >= NODES)
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


int main() {
    switch (init()) {
    case SMALL_DATA__MASTER_NODE: {
        vector<char> row(W, '0');
        vector<char> prev_row(W);
        vector<long long> score(W, 0);
        vector<long long> prev_score(W);
        for (long long i = 0; i < H; ++i) {
            swap(row, prev_row);
            swap(score, prev_score);
            for (long long j = 0; j < W; ++j) {
                char c = GetPosition(i, j);
                row[j] = c;
                score[j] = -1;
                if (c != '#') {
                    if (prev_row[j] != '#') {
                        if (prev_score[j] != -1)
                            score[j] = prev_score[j] + c - '0';
                        if (j != 0 && prev_score[j - 1] != -1) {
                            score[j] = max(score[j], prev_score[j - 1] + prev_row[j] - '0' + c - '0');
                        }
                        if (j != W - 1 && prev_score[j + 1] != -1) {
                            score[j] = max(score[j], prev_score[j + 1] + prev_row[j] - '0' + c - '0');
                        }
                    }
                }
            }
        }
        swap(row, prev_row);
        swap(score, prev_score);
        for (long long j = 0; j < W; ++j) {
            char c = '0';
            row[j] = c;
            score[j] = -1;
            if (c != '#') {
                if (prev_row[j] != '#') {
                    if (prev_score[j] != -1)
                        score[j] = prev_score[j] + c - '0';
                    if (j != 0 && prev_score[j - 1] != -1) {
                        score[j] = max(score[j], prev_score[j - 1] + prev_row[j] - '0' + c - '0');
                    }
                    if (j != W - 1 && prev_score[j + 1] != -1) {
                        score[j] = max(score[j], prev_score[j + 1] + prev_row[j] - '0' + c - '0');
                    }
                }
            }
        }

        long long result = -1;
        for (long long j = 0; j < W; ++j) {
            result = max(result, score[j]);
        }
        printf("%lld\n", result);
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }
    // ############################################

    long long real_work = WORK_FOR_THIS_NODE +
                          (IS_FIRST_NODE ? 0 : BASIC_WORK_PER_NODE) +
                          (IS_LAST_NODE ? 0 : BASIC_WORK_PER_NODE);
    long long real_beg = BEG - (IS_FIRST_NODE ? 0 : BASIC_WORK_PER_NODE);
    long long real_end = END + (IS_LAST_NODE ? 0 : BASIC_WORK_PER_NODE);

    vector<char> row(real_work, '0');
    vector<char> prev_row(real_work);
    vector<long long> score(real_work, 0);
    vector<long long> prev_score(real_work);
    //long long sub_iter = 0;
    for (long long i = 0; i < H; ++i) {
        if (i % BASIC_WORK_PER_NODE == 0) {
            // Send:
            if (!IS_FIRST_NODE) {
                for (long long j = BEG; j < BEG + BASIC_WORK_PER_NODE; ++j) {
                    PutLL(NID - 1, score[j - real_beg]);
                }
                Send(NID - 1);
            }
            if (!IS_LAST_NODE) {
                for (long long j = BEG; j < BEG + BASIC_WORK_PER_NODE; ++j) {
                    PutLL(NID + 1, score[j - real_beg]);
                }
                Send(NID + 1);
            }

            // Receive:
            if (!IS_FIRST_NODE) {
                Receive(NID - 1);
                for (long long j = real_beg; j < BEG; ++j) {
                    score[j - real_beg] = GetLL(NID - 1);
                }
            }
            if (!IS_LAST_NODE) {
                Receive(NID + 1);
                for (long long j = END; j < real_end; ++j) {
                    score[j - real_beg] = GetLL(NID + 1);
                }
            }
        }

        swap(row, prev_row);
        swap(score, prev_score);

        for (long long j = real_beg; j < real_end; ++j) {
            char c = '#';
            if (j < W)
                c = GetPosition(i, j);
            row[j - real_beg] = c;
        }

        for (long long j = real_beg; j < real_end; ++j) {
            score[j - real_beg] = -1;
            char c = row[j - real_beg];
            if (c != '#') {
                if (prev_row[j - real_beg] != '#') {
                    if (prev_score[j - real_beg] != -1)
                        score[j - real_beg] = prev_score[j - real_beg] + c - '0';
                    if (j != real_beg && prev_score[j - real_beg - 1] != -1) {
                        score[j - real_beg] = max(score[j - real_beg], prev_score[j - real_beg - 1] + prev_row[j - real_beg] - '0' + c - '0');
                    }
                    if (j != real_end - 1 && prev_score[j - real_beg + 1] != -1) {
                        score[j - real_beg] = max(score[j - real_beg], prev_score[j - real_beg + 1] + prev_row[j - real_beg] - '0' + c - '0');
                    }
                }
            }
        }
    }
    swap(row, prev_row);
    swap(score, prev_score);
    for (long long j = real_beg; j < real_end; ++j) {
        char c = '0';
        row[j - real_beg] = c;
        score[j - real_beg] = -1;
        if (c != '#') {
            if (prev_row[j - real_beg] != '#') {
                if (prev_score[j - real_beg] != -1)
                    score[j - real_beg] = prev_score[j - real_beg] + c - '0';
                if (j != real_beg && prev_score[j - real_beg - 1] != -1) {
                    score[j - real_beg] = max(score[j - real_beg], prev_score[j - real_beg - 1] + prev_row[j - real_beg] - '0' + c - '0');
                }
                if (j != real_end - 1 && prev_score[j - real_beg + 1] != -1) {
                    score[j - real_beg] = max(score[j - real_beg], prev_score[j - real_beg + 1] + prev_row[j - real_beg] - '0' + c - '0');
                }
            }
        }
    }

    long long local_result = -1;
    for (long long j = real_beg; j < real_end; ++j) {
        local_result = max(local_result, score[j - real_beg]);
    }


    PutLL(MASTER_NODE, local_result);
    Send(MASTER_NODE);


    if (NID == MASTER_NODE) {
        long long result = -1;
        for (int node = 0; node < NODES; ++node) {
            Receive(node);
            result = max(result, GetLL(node));
        }
        printf("%lld\n", result);
    }

    return 0;
}