//		AUTOR: KAROL PESZEK
//		WSZLEKIE PRAWA ZASTRZEZONE
//
//		PROGRAMOWANIE 2
//		ZADANIE B - OPERACJE ZBIOROWE
//
//		WERSJA CPP
//
//		UWAGA! BRAK FUNKCJI MAIN

void read_at_pointer(char *p, int *set) {
  if (*p == '\0')
    return;

  if (*p == ' ') {
    read_at_pointer(p + 1, set);
    return;
  }

  int d4 = !(*p - '0');
  int d3 = !(*(p + 1) - '0');
  int d2 = !(*(p + 2) - '0');
  int d1 = !(*(p + 3) - '0');
  int d0 = !(*(p + 4) - '0');

  int d = d0 | (d1 << 1) | (d2 << 2) | (d3 << 3) | (d4 << 4);

  *set = *set | (1 << d);

  read_at_pointer(p + 5, set);
}

int push(char *pos, int elem) {
  int d4 = (elem & (1 << 0)) >> 0;
  int d3 = (elem & (1 << 1)) >> 1;
  int d2 = (elem & (1 << 2)) >> 2;
  int d1 = (elem & (1 << 3)) >> 3;
  int d0 = (elem & (1 << 4)) >> 4;

  *pos = !d0 + '0';
  *(pos + 1) = !d1 + '0';
  *(pos + 2) = !d2 + '0';
  *(pos + 3) = !d3 + '0';
  *(pos + 4) = !d4 + '0';
  *(pos + 5) = ' ';

  return 6;
}

int push_if_exists(char *pos, int set, int elem_num) {
  if ((set & (1 << elem_num)) != 0)
    return push(pos, elem_num);
  return 0;
}

int count(int set) {
  return ((set & (1 << 0)) != 0) + ((set & (1 << 1)) != 0) +
         ((set & (1 << 2)) != 0) + ((set & (1 << 3)) != 0) +
         ((set & (1 << 4)) != 0) + ((set & (1 << 5)) != 0) +
         ((set & (1 << 6)) != 0) + ((set & (1 << 7)) != 0) +
         ((set & (1 << 8)) != 0) + ((set & (1 << 9)) != 0) +
         ((set & (1 << 10)) != 0) + ((set & (1 << 11)) != 0) +
         ((set & (1 << 12)) != 0) + ((set & (1 << 13)) != 0) +
         ((set & (1 << 14)) != 0) + ((set & (1 << 15)) != 0) +
         ((set & (1 << 16)) != 0) + ((set & (1 << 17)) != 0) +
         ((set & (1 << 18)) != 0) + ((set & (1 << 19)) != 0) +
         ((set & (1 << 20)) != 0) + ((set & (1 << 21)) != 0) +
         ((set & (1 << 22)) != 0) + ((set & (1 << 23)) != 0) +
         ((set & (1 << 24)) != 0) + ((set & (1 << 25)) != 0) +
         ((set & (1 << 26)) != 0) + ((set & (1 << 27)) != 0) +
         ((set & (1 << 28)) != 0) + ((set & (1 << 29)) != 0) +
         ((set & (1 << 30)) != 0) + ((set & (1 << 31)) != 0);
}

int compare_bit_rec(int set1, int set2) {
  if (((set1 & 1) == 1) && ((set2 & 1) == 0))
    return true;
  if (((set1 & 1) == 0) && ((set2 & 1) == 1))
    return false;

  return compare_bit_rec(set1 >> 1, set2 >> 1);
}

int compare(int set1, int set2) {
  if (count(set1) > count(set2))
    return true;
  if (count(set1) < count(set2))
    return false;

  return compare_bit_rec(set1, set2);
}

void Emplace(char *buff, int *set) {
  *set = 0;
  read_at_pointer(buff, set);
}

void Insert(char *buff, int *set) { read_at_pointer(buff, set); }

void Erase(char *buff, int *set) {
  int elems_to_remove = 0;
  read_at_pointer(buff, &elems_to_remove);

  *set = *set & (~elems_to_remove);
}

bool Emptiness(int set) { return set == 0; }

bool Nonempty(int set) { return set != 0; }

void Print(int set, char *target) {
  if (set == 0) {
    *target = 'e';
    *(target + 1) = 'm';
    *(target + 2) = 'p';
    *(target + 3) = 't';
    *(target + 4) = 'y';
    *(target + 5) = '\0';

    return;
  }

  target = target + push_if_exists(target, set, 0);
  target = target + push_if_exists(target, set, 1);
  target = target + push_if_exists(target, set, 2);
  target = target + push_if_exists(target, set, 3);
  target = target + push_if_exists(target, set, 4);
  target = target + push_if_exists(target, set, 5);
  target = target + push_if_exists(target, set, 6);
  target = target + push_if_exists(target, set, 7);
  target = target + push_if_exists(target, set, 8);
  target = target + push_if_exists(target, set, 9);
  target = target + push_if_exists(target, set, 10);
  target = target + push_if_exists(target, set, 11);
  target = target + push_if_exists(target, set, 12);
  target = target + push_if_exists(target, set, 13);
  target = target + push_if_exists(target, set, 14);
  target = target + push_if_exists(target, set, 15);
  target = target + push_if_exists(target, set, 16);
  target = target + push_if_exists(target, set, 17);
  target = target + push_if_exists(target, set, 18);
  target = target + push_if_exists(target, set, 19);
  target = target + push_if_exists(target, set, 20);
  target = target + push_if_exists(target, set, 21);
  target = target + push_if_exists(target, set, 22);
  target = target + push_if_exists(target, set, 23);
  target = target + push_if_exists(target, set, 24);
  target = target + push_if_exists(target, set, 25);
  target = target + push_if_exists(target, set, 26);
  target = target + push_if_exists(target, set, 27);
  target = target + push_if_exists(target, set, 28);
  target = target + push_if_exists(target, set, 29);
  target = target + push_if_exists(target, set, 30);
  target = target + push_if_exists(target, set, 31);

  *target = '\0';
}

bool Member(char *buff, int set) {
  int elem = 0;
  read_at_pointer(buff, &elem);
  return (elem & set) != 0;
}

bool Disjoint(int set1, int set2) { return (set1 & set2) == 0; }

bool Conjunctive(int set1, int set2) { return (set1 & set2) != 0; }

bool Equality(int set1, int set2) { return set1 == set2; }

bool Inclusion(int set1, int set2) { return set1 == (set1 & set2); }

void Union(int set1, int set2, int *target) { *target = set1 | set2; }

void Intersection(int set1, int set2, int *target) { *target = set1 & set2; }

void Symmetric(int set1, int set2, int *target) { *target = set1 ^ set2; }

void Difference(int set1, int set2, int *target) { *target = set1 & (~set2); }

void Complement(int set, int *target) { *target = ~set; }

int Cardinality(int set) { return count(set); }

bool LessThan(int set1, int set2) {
  if (set1 == set2)
    return false;
  return compare(set2, set1);
}

bool LessEqual(int set1, int set2) {
  if (set1 == set2)
    return true;
  return compare(set2, set1);
}

bool GreatEqual(int set1, int set2) {
  if (set1 == set2)
    return true;
  return compare(set1, set2);
}

bool GreatThan(int set1, int set2) {
  if (set1 == set2)
    return false;
  return compare(set1, set2);
}
