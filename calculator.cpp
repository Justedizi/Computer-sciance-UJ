#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2)
    return 1;

  string input = "";
  for (int i = 1; i < argc; i++)
    input += argv[i];

  string s1 = "", s2 = "";
  char op = 0;
  bool foundOp = false;

  for (int i = 0; i < input.length(); i++) {
    char c = input[i];
    if (c == ' ')
      continue;

    if (!foundOp && (c == '+' || c == '-' || c == '*' || c == '/')) {
      op = c;
      foundOp = true;
    } else {
      if (!foundOp)
        s1 += c;
      else
        s2 += c;
    }
  }

  double a = stod(s1);
  double b = stod(s2);
  double res = 0;

  if (op == '+')
    res = a + b;
  else if (op == '-')
    res = a - b;
  else if (op == '*')
    res = a * b;
  else if (op == '/' && b != 0)
    res = a / b;

  cout << res << endl;

  return 0;
}
