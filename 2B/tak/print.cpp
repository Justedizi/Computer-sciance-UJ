// KRZYSZTOF PIECHAL
#include "bitwise_operations.h"

void read_all(int n, char *p, int i, int j) {
  if (i == 31)
    return;
  int num = n << i;
  if (num) {
    if (j < 5) {
      *p += (num << j) + '0';
      read_all(n, p, i, j + 1);
    }
    *p += ' ';
  }
  read_all(n, p, i + 1, 0);
}

void Print(int n, char *p) { read_all(n, p, 0, 0); }
