// KRZYSZTOF PIECHAL
#include <cmath>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
using namespace std;

struct sub {
  bool b;
  unsigned char uc;
  float f;
  bool operator==(sub &other) {
    return (b == other.b && uc == other.uc && std::abs(f - other.f) < 1e-9);
  }
};

struct element {
  int num;
  string s;
  char c;
  sub s1;
  sub s2;
  sub s3;
  sub s4;
  bool operator==(element &other) {
    return (num == other.num && s == other.s && c == other.c &&
            s1 == other.s1 && s2 == other.s2 && s3 == other.s3 &&
            s4 == other.s4);
  }
};

void swap_elements(element *a, element *b) {
  element temp = *a;
  *a = *b;
  *b = temp;
}

bool read_sub(fstream *inp, sub *s) {
  if (!(*inp >> s->b))
    return false;
  unsigned int n;
  if (!(*inp >> n))
    return false;
  n %= 256;
  s->uc = n;
  if (!(*inp >> s->f))
    return false;
  string d;
  getline(*inp, d);
  return true;
}
bool read_element(fstream *inp, element *e) {
  if (!(*inp >> e->num))
    return 0;
  string a;
  getline(*inp, a);
  if (!getline(*inp, e->s))
    return 0;
  if (!inp->get(e->c))
    return 0;
  getline(*inp, a);
  if (!read_sub(inp, &(*e).s1))
    return 0;
  if (!read_sub(inp, &(*e).s2))
    return 0;
  if (!read_sub(inp, &(*e).s3))
    return 0;
  if (!read_sub(inp, &(*e).s4))
    return 0;
  return 1;
}

void write_sub(fstream *out, sub *s) {
  *out << (*s).b << ' ' << (int)(*s).uc << ' ' << (*s).f << endl;
}

void write_element(fstream *out, element *e) {
  *out << (*e).num << '\n' << (*e).s << '\n' << (*e).c << '\n';
  write_sub(out, &(*e).s1);
  write_sub(out, &(*e).s2);
  write_sub(out, &(*e).s3);
  write_sub(out, &(*e).s4);
}

void remove_element(fstream *source, fstream *temp1, element *e) {
  element curr;
  bool element_removed = false;
  while (read_element(source, &curr)) {
    if (!element_removed && curr == *e) {
      element_removed = true;
    } else {
      write_element(temp1, &curr);
    }
  }
}

int elements_count(string target, string temp1) {
  fstream inp(target.c_str(), ios::in);
  element e;
  int count = 0;
  while (read_element(&inp, &e)) {
    count++;
  }
  inp.close();
  return count;
}

void copy_files(string source, string taget) {
  fstream inp(source.c_str(), ios::in);
  fstream out(taget.c_str(), ios::out);
  element e;
  while (read_element(&inp, &e)) {
    write_element(&out, &e);
  }
  inp.close();
  out.close();
  return;
}

int nums_count(string counter_file, int i) {
  fstream inp(counter_file.c_str(), ios::in);
  int curr, occur = 0;
  while (inp >> curr) {
    if (curr == i)
      occur++;
  }
  inp.close();
  return occur;
}

int create_file_with_nums(string source, string counter_file) {
  fstream inp(source.c_str(), ios::in);
  fstream out(counter_file.c_str(), ios::out);
  element e;
  int count = 0;
  while (read_element(&inp, &e)) {
    out << e.num << '\n';
    count++;
  }
  inp.close();
  out.close();
  return count;
}

element *compare_elements(element *e1, element *e2, string counter_file) {
  int e1c = nums_count(counter_file, e1->num);
  int e2c = nums_count(counter_file, e2->num);
  if (e1c > e2c) {
    return e1;
  } else if (e1c < e2c) {
    return e2;
  } else {
    if (e1->num > e2->num) {
      return e1;
    } else if (e1->num < e2->num) {
      return e2;
    } else {
      int e1s = ((int)e1->s1.uc + e1->s2.uc + e1->s3.uc + e1->s4.uc) % 256;
      int e2s = ((int)e2->s1.uc + e2->s2.uc + e2->s3.uc + e2->s4.uc) % 256;
      if (e1s > e2s) {
        return e1;
      } else {
        return e2;
      }
    }
  }
}

element *compare_elements_int(element *e1, element *e2, string counter_file) {
  return (e1->num < e2->num ? e1 : e2);
  // *(e1).s === e1->num
}

element *compare_elements_str(element *e1, element *e2, string counter_file) {
  return (e1->s < e2->s ? e1 : e2);
}

void SortCount(string source_target, string temp1, string temp2) {
  create_file_with_nums(source_target, temp2);
  int e_counts = elements_count(source_target, temp1);
  if (e_counts == 0)
    return;
  bool keep_sorting = true;
  while (keep_sorting) {
    keep_sorting = 0;
    fstream inp(source_target.c_str(), ios::in);
    fstream out(temp1.c_str(), ios::out);
    element prev, curr;
    read_element(&inp, &prev);
    for (int i = 0; i < e_counts - 1; i++) {
      read_element(&inp, &curr);
      if (compare_elements(&prev, &curr, temp2) == &curr) {
        swap_elements(&prev, &curr);
        keep_sorting = true;
      }
      write_element(&out, &prev);
      prev = curr;
    }
    write_element(&out, &prev);
    inp.close();
    out.close();
    string temp = source_target;
    temp1 = source_target;
    source_target = temp;
  }
  copy_files(temp1, source_target);
}

void SymmetricDifference(string file1, string file2, string tempfile) {
  fstream inp2(file2.c_str(), ios::in);
  fstream temp_out(tempfile.c_str(), ios::out);

  element e_from_file2;
  while (read_element(&inp2, &e_from_file2)) {
    bool found_in_file1 = false;
    fstream inp1(file1.c_str(), ios::in);
    element e_from_file1;
    while (read_element(&inp1, &e_from_file1)) {
      if (e_from_file1 == e_from_file2) {
        found_in_file1 = true;
        break;
      }
    }
    inp1.close();

    if (found_in_file1) {
      write_element(&temp_out, &e_from_file2);
    } else {
      fstream append_to_file1(file1.c_str(), ios::app);
      write_element(&append_to_file1, &e_from_file2);
      append_to_file1.close();
    }
  }
  inp2.close();
  temp_out.close();

  copy_files(tempfile, file2);
}

void SortInt(string source_target, string temp1, string temp2) {
  int e_counts = elements_count(source_target, temp1);
  if (e_counts == 0)
    return;
  bool keep_sorting = true;
  while (keep_sorting) {
    keep_sorting = 0;
    fstream inp(source_target.c_str(), ios::in);
    fstream out(temp1.c_str(), ios::out);
    element prev, curr;
    read_element(&inp, &prev);
    for (int i = 0; i < e_counts - 1; i++) {
      read_element(&inp, &curr);
      if (compare_elements_int(&prev, &curr, temp2) == &curr) {
        swap_elements(&prev, &curr);
        keep_sorting = true;
      }
      write_element(&out, &prev);
      prev = curr;
    }
    write_element(&out, &prev);
    inp.close();
    out.close();
    copy_files(temp1, source_target);
  }
}

void SortString(string source_target, string temp1, string temp2) {
  int e_counts = elements_count(source_target, temp1);
  if (e_counts == 0)
    return;
  bool keep_sorting = true;
  while (keep_sorting) {
    keep_sorting = 0;
    fstream inp(source_target.c_str(), ios::in);
    fstream out(temp1.c_str(), ios::out);
    element prev, curr;
    read_element(&inp, &prev);
    for (int i = 0; i < e_counts - 1; i++) {
      read_element(&inp, &curr);
      if (compare_elements_str(&prev, &curr, temp2) == &curr) {
        swap_elements(&prev, &curr);
        keep_sorting = true;
      }
      write_element(&out, &prev);
      prev = curr;
    }
    write_element(&out, &prev);
    inp.close();
    out.close();
    copy_files(temp1, source_target);
  }
}
