// KRZYSZTOF PIECHAL
#include "bitwise_operations.h"

int traverse_all2(int *n, int i, bool stop, int ones) {
  if (i == 32) {
    return ones;
  }
  if (*n & (1 << i)) {
    if (stop)
      return true;
    ones++;
  }
  return traverse_all2(n, i + 1, stop, ones);
}

int Cardinality(int n) { return traverse_all2(&n, 0, false, 0); }
