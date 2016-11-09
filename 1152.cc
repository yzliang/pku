#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int GetNum(char c) {
  if (isdigit(c)) {
    return c - '0';
  } else if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 10;
  } else {
    return c - 'a' + 36;
  }
}

int Solve(const string& s) {
  int n = 2;
  for (int i = 0; i < s.size(); ++i) {
    n = max(n, GetNum(s[i]) + 1);
  }
  while (n <= 62) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
      res = (res * n + GetNum(s[i])) % (n - 1);
    }
    if (res == 0) {
      return n;
    }
    ++n;
  }
  return -1;
}

int main() {
  string s;
  while (cin >> s) {
    int ans = Solve(s);
    if (ans > 0)
      cout << ans << endl;
    else
      cout << "such number is impossible!" << endl;
  }
  return 0;
}
