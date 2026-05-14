// Author: Jan Kowalski
#include <string>
#include <cstdarg>
using namespace std;

// --- helpers dla Mult ---
static int mc(const string& a, const string& b) {
    if (a.size() > b.size()) return 1;
    if (a.size() < b.size()) return -1;
    if (a.empty()) return 0;
    if (a[0] > b[0]) return 1;
    if (a[0] < b[0]) return -1;
    return mc(a.substr(1), b.substr(1));
}

static string msz(const string& s) {  // strip leading zeros
    if (s.empty()) return "0";
    if (s[0] != '0') return s;
    return msz(s.substr(1));
}

static string mav(const string& s) {  // absolute value
    return s[0] == '-' ? s.substr(1) : s;
}

static string dmul(const string& a, char d, char c) {
    if (a.empty() && c == 0) return "";
    int da = a.empty() ? 0 : (a.back() - '0');
    int p = da * d + c;
    string sa = a.empty() ? "" : a.substr(0, (int)a.size() - 1);
    string r = dmul(sa, d, p / 10);
    return r + (char)(p % 10 + '0');
}

static string digitMul(const string& a, char d) {
    if (d == 0) return "0";
    if (d == 1) return a;
    return msz(dmul(a, d, 0));
}

static string apm(const string& a, const string& b, char c) {  // add positive
    if (a.empty() && b.empty()) return (c ? "1" : "");
    int da = a.empty() ? 0 : (a.back() - '0');
    int db = b.empty() ? 0 : (b.back() - '0');
    int s = da + db + c;
    string sa = a.empty() ? "" : a.substr(0, (int)a.size() - 1);
    string sb = b.empty() ? "" : b.substr(0, (int)b.size() - 1);
    string r = apm(sa, sb, (char)(s / 10));
    return r + (char)(s % 10 + '0');
}

static string spm(const string& a, const string& b, char c) {  // sub positive (a >= b)
    if (a.empty() && b.empty()) return "";
    int da = a.empty() ? 0 : (a.back() - '0');
    int db = b.empty() ? 0 : (b.back() - '0');
    int d = da - db - c;
    char nb = 0;
    if (d < 0) { d += 10; nb = 1; }
    string sa = a.empty() ? "" : a.substr(0, (int)a.size() - 1);
    string sb = b.empty() ? "" : b.substr(0, (int)b.size() - 1);
    string r = spm(sa, sb, nb);
    return r + (char)(d + '0');
}

// --- big multiply (unsigned strings) ---
static string mabs(const string& a, const string& b) {
    string av = msz(a), bv = msz(b);
    if (av == "0" || bv == "0") return "0";
    if (bv == "1") return av;
    char d = bv.back() - '0';
    string rest = bv.substr(0, (int)bv.size() - 1);
    string partial = digitMul(av, d);
    string restProd = mabs(av, rest);
    string shifted = restProd + "0";
    return msz(apm(partial, shifted, 0));
}

// --- signed multiply ---
static string msig(const string& a, const string& b) {
    bool na = (a.size() > 1 && a[0] == '-');
    bool nb = (b.size() > 1 && b[0] == '-');
    string av = mav(a), bv = mav(b);
    string r = mabs(av, bv);
    if (r == "0") return "0";
    bool neg = na ^ nb;
    return neg ? "-" + r : r;
}

// --- norm ---
static string mnorm(const string& s) {
    if (s.empty()) return "0";
    if (s[0] == '-') {
        string ab = msz(s.substr(1));
        return ab == "0" ? "0" : "-" + ab;
    }
    return msz(s);
}

// --- recursive collectors ---
static string marrR(const string* a, int c) {
    if (c == 1) return mnorm(a[0]);
    return msig(a[0], marrR(a + 1, c - 1));
}

static string mvarR(int c, va_list& ap) {
    string f = va_arg(ap, const char*);
    if (c == 1) return mnorm(f);
    return msig(f, mvarR(c - 1, ap));
}

// --- exported overloads ---
string Mult(int c, const string* a) {
    return marrR(a, c);
}

string Mult(int c, ...) {
    va_list ap;
    va_start(ap, c);
    string r = mvarR(c, ap);
    va_end(ap);
    return r;
}

void Mult(string* res, int c, const string* a) {
    *res = marrR(a, c);
}

void Mult(string* res, int c, ...) {
    va_list ap;
    va_start(ap, c);
    *res = mvarR(c, ap);
    va_end(ap);
}

void Mult(string& res, int c, const string* a) {
    res = marrR(a, c);
}

void Mult(string& res, int c, ...) {
    va_list ap;
    va_start(ap, c);
    res = mvarR(c, ap);
    va_end(ap);
}
