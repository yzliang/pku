#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int n, m, len;
int s[64];
bool used[64];

bool search(int p, int q, int sum) {
  if (p == m) return true;
  if (sum == 0) {
    while (used[q]) q++;
    used[q] = true;
    if (s[q] == len) {
      if (search(p + 1, 0, 0)) return true;
    } else {
      if (search(p, q + 1, sum + s[q])) return true;
    }
    used[q] = false;
    return false;
  }
  // The extactly right stick...
  for (int i = q; i < n; i++) {
    if (!used[i] && sum + s[i] == len) {
      used[i] = true;
      if (search(p + 1, 0, 0)) return true;
      used[i] = false;
      return false;
    } else if (sum + s[i] < len)
      break;
  }
  for (; q < n; q++) {
    if (used[q] || sum + s[q] > len) continue;
    used[q] = true;
    if (search(p, q + 1, sum + s[q])) return true;
    used[q] = false;
  }
  return false;
}

int main() {
  while (cin >> n) {
    if (n == 0) break;
    int sum = 0;
    for (int i = 0; i < n; i++) {
      cin >> s[i];
      sum += s[i];
    }
    sort(s, s + n, greater<int>());
    for (len = s[0]; len <= sum; len++) {
      if (sum % len != 0) continue;
      m = sum / len;
      // m sticks of length len.
      memset(used, 0, sizeof(used));
      if (search(0, 0, 0)) {
        cout << len << endl;
        break;
      }
    }
  }
  return 0;
}
