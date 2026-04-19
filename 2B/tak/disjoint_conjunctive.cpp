// KRZYSZTOF PIECHAL
#include "bitwise_operations.h"

bool Disjoint(int n, int m) { return (n & m); }

bool Conjunctive(int n, int m) { return !(n & m); }
