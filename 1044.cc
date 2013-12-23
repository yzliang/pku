#include <algorithm>
#include <iostream>
#include <stdint.h>
using namespace std;

int n;
int a[20], b[20], y[20];

int extended_euclid(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  } else {
    int xx, yy;
    int d = extended_euclid(b, a % b, xx, yy);
    x = yy;
    y = xx - a / b * yy;
    return d;
  }
}

int modulo(int64_t x, int y) {
  int ret = x % y;
  return x >= 0 ? x : x + y;
}

int64_t min_x(int64_t p, int64_t q, int64_t bound) {
  int64_t k;
  if (bound >= q)
    k = (bound - q + p - 1) / p;
  else
    k = (bound - q) / p;
  return p * k + q;
}

int compute() {
  // let the solution space be x = p * k + q
  int64_t p = b[0] - a[0], q = y[0];
  int64_t bound = a[0];
  int64_t ans = min_x(p, q, bound);
  if (ans >= 10000) return -1;
  for (int i = 1; i < n; i++) {
    // p * k + q === y[i] (% mod).
    // c * k === e (% mod).
    int mod = b[i] - a[i];
    int c = modulo(p, mod);
    int e = modulo(y[i] - q, mod);
    // c * r + mod * s = gcd(c, mod) = d
    int r, s;
    int d = extended_euclid(c, mod, r, s);
    if (e % d != 0) return -1;
    // x = p * k + q = p * (r + s * k') + q
    s = mod / d;
    r = modulo(r * e / d, s);
    // let k be k'
    q += p * r;
    p *= s;
    // Prevent overflow.
    // x = p * k + q >= max(a[0], ..., a[i])
    // p >= 0, q >= 0
    bound = max<int64_t>(bound, a[i]);
    ans = min_x(p, q, bound);
    if (ans >= 10000) return -1;
  }
  return ans;
}

int main() {
  int t = 0;
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; i++)
      cin >> y[i] >> a[i] >> b[i];
    int ans = compute();
    cout << "Case #" << ++t << ':' << endl;
    if (ans == -1)
      cout << "Unknown bugs detected." << endl;
    else
      cout << "The actual year is " << ans << '.' << endl;
    cout << endl;
  }
  return 0;
}
