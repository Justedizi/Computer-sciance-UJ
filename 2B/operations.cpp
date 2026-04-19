// KRZYSZTOF PIECHAL
#include "bitwise_operations.h"

void Union(int n, int m, int *target) { *target = m | n; }
void Intersection(int n, int m, int *target) { *target = n & m; }
void Symmetric(int n, int m, int *target) { *target = n ^ m; }
void Difference(int n, int m, int *target) { *target = n & (~m); }
void Complement(int n, int *target) { *target = ~n; }
