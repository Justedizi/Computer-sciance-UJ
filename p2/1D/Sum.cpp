// Author: Your Name
#include <string>
#include <cstdarg>
using namespace std;

int cmpAbs(const string& a, const string& b) {
    if (a.size() > b.size()) return 1;
    if (a.size() < b.size()) return -1;
    if (a.empty()) return 0;
    if (a[0] > b[0]) return 1;
    if (a[0] < b[0]) return -1;
    return cmpAbs(a.substr(1), b.substr(1));
}

string stripZ(const string& s) {
    if (s.empty()) return "0";
    if (s[0] != '0') return s;
    return stripZ(s.substr(1));
}

string absV(const string& s) {
    return s[0] == '-' ? s.substr(1) : s;
}

string addPosRec(const string& a, const string& b, int c) {
    if (a.empty() && b.empty()) {
        return c ? "1" : "";
    }
    int da = a.empty() ? 0 : a.back() - '0';
    int db = b.empty() ? 0 : b.back() - '0';
    int s = da + db + c;
    string sa = a.empty() ? "" : a.substr(0, (int)a.size() - 1);
    string sb = b.empty() ? "" : b.substr(0, (int)b.size() - 1);
    string r = addPosRec(sa, sb, s / 10);
    return r + (char)(s % 10 + '0');
}

string addPos(const string& a, const string& b) {
    return stripZ(addPosRec(a, b, 0));
}

string subPosRec(const string& a, const string& b, int bw) {
    if (a.empty() && b.empty()) return "";
    int da = a.empty() ? 0 : a.back() - '0';
    int db = b.empty() ? 0 : b.back() - '0';
    int d = da - db - bw;
    int nb = 0;
    if (d < 0) { d += 10; nb = 1; }
    string sa = a.empty() ? "" : a.substr(0, (int)a.size() - 1);
    string sb = b.empty() ? "" : b.substr(0, (int)b.size() - 1);
    string r = subPosRec(sa, sb, nb);
    return r + (char)(d + '0');
}

string subPos(const string& a, const string& b) {
    return stripZ(subPosRec(a, b, 0));
}

string addSigned(const string& a, const string& b) {
    string av = absV(a), bv = absV(b);
    bool na = (a[0] == '-'), nb = (b[0] == '-');
    if (na == nb) {
        string r = addPos(av, bv);
        if (na && r != "0") return "-" + r;
        return r;
    }
    int cm = cmpAbs(av, bv);
    if (cm == 0) return "0";
    if (cm > 0) {
        string r = subPos(av, bv);
        return na ? "-" + r : r;
    }
    string r = subPos(bv, av);
    return nb ? "-" + r : r;
}

string norm(const string& s) {
    if (s.empty()) return "0";
    if (s[0] == '-') {
        string ab = stripZ(s.substr(1));
        return ab == "0" ? "0" : "-" + ab;
    }
    return stripZ(s);
}

string sumArrR(const string* a, int c) {
    if (c == 1) return norm(a[0]);
    return addSigned(a[0], sumArrR(a + 1, c - 1));
}

string sumVarR(int c, va_list& ap) {
    string f = va_arg(ap, const char*);
    if (c == 1) return norm(f);
    return addSigned(f, sumVarR(c - 1, ap));
}

string Sum(int c, const string* a) {
    return sumArrR(a, c);
}

string Sum(int c, ...) {
    va_list ap;
    va_start(ap, c);
    string r = sumVarR(c, ap);
    va_end(ap);
    return r;
}

void Sum(string* res, int c, const string* a) {
    *res = sumArrR(a, c);
}

void Sum(string* res, int c, ...) {
    va_list ap;
    va_start(ap, c);
    *res = sumVarR(c, ap);
    va_end(ap);
}

void Sum(string& res, int c, const string* a) {
    res = sumArrR(a, c);
}

void Sum(string& res, int c, ...) {
    va_list ap;
    va_start(ap, c);
    res = sumVarR(c, ap);
    va_end(ap);
}
