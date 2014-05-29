#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

string s;
bool f[256][256], checked[256][256];

bool check(int p, int q) {
  if (p > q)
    return false;
  if (checked[p][q])
    return f[p][q];
  checked[p][q] = true;
  // Rule 1.
  if (p == q) {
    f[p][q] = s[p] >= 'p' && s[p] <= 'z';
    return f[p][q];
  }
  // Rule 2.
  if (s[p] == 'N' && check(p + 1, q)) {
    f[p][q] = true;
    return true;
  }
  // Rule 3.
  if (s[p] == 'C' || s[p] == 'D' || s[p] == 'E' || s[p] == 'I') {
    for (int i = p + 1; i < q; i++) {
      if (check(p + 1, i) && check(i + 1, q)) {
        f[p][q] = true;
        return true;
      }
    }
  }
  f[p][q] = false;
  return false;
}

int main() {
  while (cin >> s) {
    memset(checked, 0, sizeof(checked));
    cout << (check(0, s.size() - 1) ? "YES" : "NO") << endl;
  }
  return 0;
}
