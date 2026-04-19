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
bool compare_bits(int n, int m) {
  if (((n & 1) == 1) && ((m & 1) == 0))
    return true;
  if (((n & 1)) == 0 && ((m & 1) == 1))
    return false;
  return compare_bits(n >> 1, m >> 1);
}

bool compare(int n, int m) {
  int c1 = traverse_all2(&n, 0, false, 0);
  int c2 = traverse_all2(&m, 0, false, 0);
  if (c1 > c2)
    return true;
  else if (c1 < c2)
    return false;
  return true;
}

bool LessThan(int n, int m) { return !compare(n, m); }
bool LessEqual(int n, int m) {
  if (n == m)
    return true;
  return !compare(n, m);
}
bool GreatEqual(int n, int m) {
  if (n == m)
    return true;
  return compare(n, m);
}
bool GreatThan(int n, int m) { return compare(n, m); }
