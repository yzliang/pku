#include <iostream>
using namespace std;

int main() {
  int n;
  int cache[15] = {0};
  while (cin >> n) {
    if (n == 0) break;
    if (cache[n] != 0) {
      cout << cache[n] << endl;
      continue;
    }
    int m = n + 1;
    while (true) {
      int i = n * 2, j = (m - 1) % i;
      while (i > n && j >= n) {
        i--;
        j = (j + m - 1) % i;
      }
      if (i == n) {
        cout << m << endl;
        cache[n] = m;
        break;
      }
      if (m % n == 0)
        m += n + 1;
      else
        m++;
    }
  }
  return 0;
}
