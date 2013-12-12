#include <iostream>
using namespace std;

int main() {
  int n;
  while (cin >> n) {
    if (n == 0) break;
    for (int m = n + 1; ; m++) {
      int i = n * 2, j = (m - 1) % i;
      while (i > n && j >= n) {
        i--;
        j = (j + m - 1) % i;
      }
      if (i == n) {
        cout << m << endl;
        break;
      }
    }
  }
  return 0;
}
