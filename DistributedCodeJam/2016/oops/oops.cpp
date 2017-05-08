#include <message.h>
#include <stdio.h>
#include <climits>
#include "oops.h"

#define MASTER_NODE 7
#define DONE -1

int main() {
  long long N = GetN();
  long long nodes = NumberOfNodes();
  long long my_id = MyNodeId();
  long long _min = LLONG_MAX;
  long long _max = LLONG_MIN;
  int found = 0;
  for (long long i = my_id; i < N; i += nodes) {
    long long number = GetNumber(i);
    if(found == 0) {
      found = 1;
      _min = number;
      _max = number;
    }
    else {
      if(_min > number) {
        _min = number;
      }
      if(_max < number) {
        _max = number;
      }
    }
  }
  if (found == 1) {
    PutLL(MASTER_NODE, 1);
    PutLL(MASTER_NODE, _min);
    PutLL(MASTER_NODE, _max);
  }
  PutLL(MASTER_NODE, DONE);
  Send(MASTER_NODE);

  if (my_id == MASTER_NODE) {
    long long global_min = LLONG_MAX;
    long long global_max = LLONG_MIN;
    for (int node = 0; node < nodes; ++node) {
      long long received1 = 0;
      long long received2 = 0;
      Receive(node);
      received1 = GetLL(node);
      if(received1 == 1) {
        received1 = GetLL(node);
        received2 = GetLL(node);
        if(global_min > received1) {
          global_min = received1;
        }
        if(global_max < received2) {
          global_max = received2;
        }
      }
    }
    printf("%lld\n", global_max - global_min);
  }
  return 0;
}