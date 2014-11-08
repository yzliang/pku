#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string s;
int f[100][100];
const int BIG = 1000;
char bro[128];

bool is_left(char c) {
  return c == '(' || c == '[';
}

bool is_right(char c) {
  return c == ')' || c == ']';
}

void print(int l, int r) {
  if (l == r) {
    if (s[l] == '(' || s[l] == ')')
      cout << "()";
    else
      cout << "[]";
  } else if (is_left(s[l]) && f[l][r] == f[l + 1][r] + 1) {
    cout << s[l];
    print(l + 1, r);
    cout << bro[s[l]];
  } else if (is_right(s[r]) && f[l][r] == f[l][r - 1] + 1) {
    cout << bro[s[r]];
    print(l, r - 1);
    cout << s[r];
  } else if (is_left(s[l]) && s[l] == bro[s[r]] && f[l][r] == f[l + 1][r - 1]) {
    cout << s[l];
    print(l + 1, r - 1);
    cout << s[r];
  } else {
    for (int i = l; i < r; i++) {
      if (f[l][r] == f[l][i] + f[i + 1][r]) {
        print(l, i);
        print(i + 1, r);
        break;
      }
    }
  }
}

int main() {
  bro['('] = ')';
  bro[')'] = '(';
  bro['['] = ']';
  bro[']'] = '[';
  getline(cin, s);
  if (s[s.size() - 1] == '\r')
    s.erase(s.end() - 1);
  if (s.empty()) {
    cout << endl;
    return 0;
  }
  for (int i = 0; i < s.size(); i++)
    f[i][i] = 1;
  for (int len = 2; len <= s.size(); len++) {
    for (int l = 0; l + len <= s.size(); l++) {
      int r = l + len - 1;
      f[l][r] = BIG;
      if (is_left(s[l]))
        f[l][r] = min(f[l][r], f[l + 1][r] + 1);
      if (is_right(s[r]))
        f[l][r] = min(f[l][r], f[l][r - 1] + 1);
      if (is_left(s[l]) && s[l] == bro[s[r]])
        f[l][r] = min(f[l][r], f[l + 1][r - 1]);
      // Split.
      for (int i = l; i < r; i++)
        f[l][r] = min(f[l][r], f[l][i] + f[i + 1][r]);
    }
  }
  print(0, s.size() - 1);
  cout << endl;
  return 0;
}
