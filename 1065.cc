#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
using namespace std;

struct Stick {
  int w, l;
  bool operator<(const Stick& that) const {
    if (l == that.l)
      return w < that.w;
    else
      return l < that.l;
  }
};

int n;
Stick s[5000];
int tail[5001];

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> s[i].l >> s[i].w;
    sort(s, s + n);
    memset(tail, 0, sizeof(tail));
    tail[0] = INT_MAX;
    for (int i = 0; i < n; i++) {
      int l = 0, r = i;
      while (l <= r) {
        int m = l + (r - l) / 2;
        if (tail[m] > s[i].w)
          l = m + 1;
        else
          r = m - 1;
      }
      tail[r + 1] = s[i].w;
    }
    int ans = n;
    while (tail[ans] == 0)
      ans--;
    cout << ans << endl;
  }
  return 0;
}
