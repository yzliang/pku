#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

struct Man {
  int t, p, s;
  bool operator<(const Man& that) const {
    return t < that.t;
  }
};

int n, k, t;
Man men[100];
int f[2][101];

int main() {
  cin >> n >> k >> t;
  for (int i = 0; i < n; i++)
    cin >> men[i].t;
  for (int i = 0; i < n; i++)
    cin >> men[i].p;
  for (int i = 0; i < n; i++)
    cin >> men[i].s;
  sort(men, men + n);
  int next = 0;  // men iterator.
  while (men[next].t == 0)
    next++;
  for (int i = 1; i <= k; i++)
    f[0][i] = -1;
  for (int i = 1; i <= t; i++) {
    int from = (i + 1) % 2, to = i % 2;
    for (int j = 0; j <= k; j++) {
      f[to][j] = f[from][j];
      if (j > 0)
        f[to][j] = max(f[to][j], f[from][j - 1]);
      if (j < k)
        f[to][j] = max(f[to][j], f[from][j + 1]);
    }
    while (next < n && men[next].t == i) {
      if (f[to][men[next].s] != -1)
        f[to][men[next].s] += men[next].p;
      next++;
    }
  }
  int ans = 0;
  for (int i = 0; i <= k; i++)
    ans = max(ans, f[t % 2][i]);
  cout << ans << endl;
  return 0;
}
