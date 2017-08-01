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
#include "number_bases.h"
using namespace std;

int NODES = NumberOfNodes();
int NID = MyNodeId();
long long N = GetLength();
#define MASTER_NODE (NODES - 1)

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
}


int main() {
    switch (init()) {
    case SMALL_DATA__MASTER_NODE: {
        long long max_digit = 0;
        long long result = 0;
        long long remn = 0;
        for (long long i = 0; i < N; ++i) {
            long long x = GetDigitX(i);
            long long y = GetDigitY(i);
            long long z = GetDigitZ(i);
            max_digit = max(max_digit, max(x, max(y, z)));
            if (x + y + remn == z) {
                if (result == 0)
                    ; // OK
                else if (result != 0 && result > max_digit)
                    ; // OK
                else {
                    result = -1;
                    break;
                }
                remn = 0;
            }
            else if (x + y + remn > z) {
                long long possibleB = x + y + remn - z;
                if (possibleB > max_digit) {
                    if (result == 0)
                        result = possibleB;
                    else if (result != possibleB) {
                        result = -1;
                        break;
                    }
                }
                else {
                    result = -1;
                    break;
                }
                remn = 1;
            }
            else {
                result = -1;
                break;
            }
        }
              
        if (remn != 0) {
            printf("IMPOSSIBLE\n");
        }
        else if (result == -1) {
            printf("IMPOSSIBLE\n");
        }
        else if (result == 0) {
            printf("NON-UNIQUE\n");
        }
        else {
            printf("%lld\n", result);
        }
        return 0;
    }
    case SMALL_DATA__OTHER_NODES:
        return 0;
    case NORMAL_MODE:
        ;
    }
    // ########################################################

    long long max_digit = 0;
    long long result0 = 0;
    long long result1 = 0;
    long long remn0 = 0;
    long long remn1 = 1;
    for (long long i = BEG; i < END; ++i) {
        long long x = GetDigitX(i);
        long long y = GetDigitY(i);
        long long z = GetDigitZ(i);
        max_digit = max(max_digit, max(x, max(y, z)));


        if (x + y + remn0 == z) {
            if (result0 == 0)
                ; // OK
            else if (result0 != 0 && result0 > max_digit)
                ; // OK
            else {
                result0 = -1;
            }
            remn0 = 0;
        }
        else if (x + y + remn0 > z) {
            long long possibleB = x + y + remn0 - z;
            if (possibleB > max_digit) {
                if (result0 == 0)
                    result0 = possibleB;
                else if (result0 != possibleB) {
                    result0 = -1;
                }
            }
            else {
                result0 = -1;
            }
            remn0 = 1;
        }
        else {
            result0 = -1;
        }



        if (x + y + remn1 == z) {
            if (result1 == 0)
                ; // OK
            else if (result1 != 0 && result1 > max_digit)
                ; // OK
            else {
                result1 = -1;
            }
            remn1 = 0;
        }
        else if (x + y + remn1 > z) {
            long long possibleB = x + y + remn1 - z;
            if (possibleB > max_digit) {
                if (result1 == 0)
                    result1 = possibleB;
                else if (result1 != possibleB) {
                    result1 = -1;
                }
            }
            else {
                result1 = -1;
            }
            remn1 = 1;
        }
        else {
            result1 = -1;
        }
    }

    long long prev_max_digit = 0;
    long long prev_remn = 0;
    long long prev_result = 0;
    if (NID > 0) {
        Receive(NID - 1);
        prev_max_digit = GetLL(NID - 1);
        prev_remn = GetLL(NID - 1);
        prev_result = GetLL(NID - 1);
    }

    max_digit = max(max_digit, prev_max_digit);

    if (result0 != 0 && max_digit >= result0) {
        result0 = -1;
    }
    if (result1 != 0 && max_digit >= result1) {
        result1 = -1;
    }

    if (prev_remn == 0) {
        result1 = -1;
    }
    if (prev_remn != 0) {
        result0 = -1;
    }

    if (prev_result != 0) {
        if (result0 == 0)
            result0 = prev_result;
        else if (prev_result != result0)
            result0 = -1;

        if (result1 == 0)
            result1 = prev_result;
        else if (prev_result != result1)
            result1 = -1;
    }

    long long remn = 0;
    long long result = -1;
    if (result0 != -1) {
        remn = remn0;
        result = result0;
    }
    else if (result1 != -1) {
        remn = remn1;
        result = result1;
    }

    if (NID == MASTER_NODE) {
        if (remn != 0) {
            printf("IMPOSSIBLE\n");
        }
        else if (result == -1) {
            printf("IMPOSSIBLE\n");
        }
        else if (result == 0) {
            printf("NON-UNIQUE\n");
        }
        else {
            printf("%lld\n", result);
        }
    }
    else {
        PutLL(NID + 1, max_digit);
        PutLL(NID + 1, remn);
        PutLL(NID + 1, result);
        Send(NID + 1);
    }

    return 0;
}