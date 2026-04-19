// KRZYSZTOF PIECHAL
#include "bitwise_operations.h"

bool Inclusion(int n, int m) { return n == (n & m); }

bool Equality(int n, int m) { return n == m; }
