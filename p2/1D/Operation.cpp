// Author: Jan Kowalski
#include <string>
#include <cstdarg>
using namespace std;

typedef string (*FPtr)(int, const string*);
typedef void (*VPtr)(string*, int, const string*);

static string opFPAccR(FPtr f, string acc, int left, va_list& ap) {
    if (left == 0) return acc;
    string s = va_arg(ap, const char*);
    const string arr[2] = {acc, s};
    string next = f(2, arr);
    return opFPAccR(f, next, left - 1, ap);
}

static string opFPVaR(FPtr f, int c, va_list& ap) {
    string first = va_arg(ap, const char*);
    return opFPAccR(f, first, c - 1, ap);
}

static void opVPAccR(VPtr f, string& acc, int left, va_list& ap) {
    if (left == 0) return;
    string s = va_arg(ap, const char*);
    string next;
    const string arr[2] = {acc, s};
    f(&next, 2, arr);
    acc = next;
    opVPAccR(f, acc, left - 1, ap);
}

static void opVPVaR(VPtr f, string& res, int c, va_list& ap) {
    res = va_arg(ap, const char*);
    opVPAccR(f, res, c - 1, ap);
}

string Operation(FPtr f, int c, const string* a) {
    return f(c, a);
}

string Operation(FPtr f, int c, ...) {
    va_list ap;
    va_start(ap, c);
    string r = opFPVaR(f, c, ap);
    va_end(ap);
    return r;
}

void Operation(string* res, FPtr f, int c, ...) {
    va_list ap;
    va_start(ap, c);
    *res = opFPVaR(f, c, ap);
    va_end(ap);
}

void Operation(string* res, FPtr f, int c, const string* a) {
    *res = f(c, a);
}

void Operation(string& res, VPtr f, int c, const string* a) {
    f(&res, c, a);
}

void Operation(string& res, VPtr f, int c, ...) {
    va_list ap;
    va_start(ap, c);
    opVPVaR(f, res, c, ap);
    va_end(ap);
}
