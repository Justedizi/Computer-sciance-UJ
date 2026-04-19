// KRZYSZTOF PIECHAL
#include "bitwise_operations.h"

void Insert(char *p, int *n) {
  if (*p == '\0')
    return;
  if (*p == ' ')
    return Insert(p + 1, n);
  int sum = (*(p) - '0') + ((*(p + 1) - '0') << 1) + ((*(p + 2) - '0') << 2) +
            ((*(p + 3) - '0') << 3) + ((*(p + 4) - '0') << 4);
  *n |= 1 << sum;
  return Insert(p + 5, n);
}

void Emplace(char *p, int *n) {
  *n = 0;
  Insert(p, n);
}
bool Member(char *p, int n) {
  int temp = 0;
  Emplace(p, &temp);
  return n & temp;
}
