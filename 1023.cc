#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <string>
using namespace std;

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    int64_t k, n;
    string s, num;
    cin >> k >> s >> n;
    reverse(s.begin(), s.end());
    for (int i = 0; i < k; i++) {
      if (n % 2 == 0) {
        num += '0';
        n /= 2;
      } else {
        if (s[i] == 'n' && n == 0x7fffffffffffffff) break;
        if (s[i] == 'p' && n == 0x8000000000000000) break;
        num += '1';
        n = (n - (s[i] == 'p' ? 1 : -1)) / 2;
      }
    }
    if (n == 0) {
      reverse(num.begin(), num.end());
      cout << num << endl;
    } else
      cout << "Impossible" << endl;
  }
  return 0;
}
