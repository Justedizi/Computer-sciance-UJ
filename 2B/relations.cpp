// KRZYSZTOF PIECHAL
#include "bitwise_operations.h"

bool compare_bits(int n, int m) {
  if (((n & 1) == 1) && ((m & 1) == 0))
    return true;
  if (((n & 1)) == 0 && ((m & 1) == 1))
    return false;
  return compare_bits(n >> 1, m >> 1);
}

bool compare(int n, int m) {
  int c1 = traverse_all(&n, 0, false, 0);
  int c2 = traverse_all(&m, 0, false, 0);
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
