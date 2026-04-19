// KRZYSZTOF PIECHAL
#include "bitwise_operations.h"

int traverse_all(int *n, int i, bool stop, int ones) {
  if (i == 32) {
    return ones;
  }
  if (*n & (1 << i)) {
    if (stop)
      return true;
    ones++;
  }
  return traverse_all(n, i + 1, stop, ones);
}

bool Emptiness(int n) { return traverse_all(&n, 0, true, 0); }
bool Nonempty(int n) { return !Emptiness(n); }
