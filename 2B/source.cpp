// KRZYSZTOF PIECHAL
#include <iostream>

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

void Erase(char *p, int *n) {
  if (*p == '\0')
    return;
  if (*p == ' ')
    return Erase(p + 1, n);
  int sum = (*(p) - '0') + ((*(p + 1) - '0') << 1) + ((*(p + 2) - '0') << 2) +
            ((*(p + 3) - '0') << 3) + ((*(p + 4) - '0') << 4);
  *n &= 0 << sum;
  return Erase(p + 5, n);
}

void read_all(int n, char *p, int i, int j) {
  if (i == 32)
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

bool Member(char *p, int n) {
  int temp = 0;
  Emplace(p, &temp);
  return n & temp;
}

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

bool Disjoint(int n, int m) { return (n & m); }
bool Conjunctive(int n, int m) { return !(n & m); }
bool Equality(int n, int m) { return n == m; }
bool Inclusion(int n, int m) { return n == (n & m); }
void Union(int n, int m, int *target) { *target = m | n; }
void Intersection(int n, int m, int *target) { *target = n & m; }
void Symmetric(int n, int m, int *target) { *target = n ^ m; }
void Difference(int n, int m, int *target) { *target = n & (~m); }
void Complement(int n, int *target) { *target = ~n; }
int Cardinality(int n) { return traverse_all(&n, 0, false, 0); }
bool LessThan(int n, int m) { return !compare(n, m); }
bool LessEqual(int n, int m) {
  if (n == m)
    return true;
  return !compare(n, m);
}
bool GreatThan(int n, int m) { return compare(n, m); }
bool GreatEqual(int n, int m) {
  if (n == m)
    return true;
  return compare(n, m);
}
