#include <iostream>
#include <stdint.h>
using namespace std;

int64_t extended_euclid(int64_t a, int64_t b, int64_t& x, int64_t& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  } else {
    int64_t xx, yy;
    int64_t d = extended_euclid(b, a % b, xx, yy);
    x = yy;
    y = (xx - a / b * yy);
    return d;
  }
}

int main() {
  int64_t x, y, m, n, l;
  cin >> x >> y >> m >> n >> l;
  int64_t a = m - n, b = y - x;
  if (a < 0) {
    a = -a;
    b = -b;
  }
  b = ((b % l) + l) % l;
  int64_t d = extended_euclid(a, l, x, y);  // d = a * x + l * y
  if (b % d != 0)
    cout << "Impossible" << endl;
  else {
    // solution = x0 + k * (l / d)
    int64_t x0 = b / d * x, co = l / d;
    int64_t k;
    if (x0 <= 0)
      k = (-x0 + co - 1) / co;
    else
      k = -x0 / co;
    cout << x0 + k * co << endl;
  }
  return 0;
}
