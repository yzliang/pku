#include <cmath>
#include <iostream>
using namespace std;

int gcd(int a, int b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

int main() {
  bool first = true;
  int n, m;
  while (cin >> n >> m) {
    if (first)
      first = false;
    else
      cout << endl;
    int d = gcd(n, m);
    n /= d;
    m /= d;
    int a, b;
    for (int i = 1; i < m; i++) {
      int j = round((double) i * n / m);
      if (i == 1 || fabs((double) j / i - (double) n / m) <
          fabs((double) a / b - (double) n / m)) {
        cout << j << '/' << i << endl;
        a = j;
        b = i;
      }
    }
    cout << n << '/' << m << endl;
  }
  return 0;
}
