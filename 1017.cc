#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  int a[7];
  while (true) {
    int sum = 0;
    for (int i = 1; i <= 6; i++) {
      cin >> a[i];
      sum += a[i];
    }
    if (sum == 0) break;
    int ans = a[6] + a[5] + a[4];
    // Fill 5.
    a[1] = max(0, a[1] - a[5] * 11);
    // Fill 4.
    if (a[2] >= a[4] * 5) {
      a[2] -= a[4] * 5;
    } else {
      a[1] = max(0, a[1] - 4 * (a[4] * 5 - a[2]));
      a[2] = 0;
    }
    // Pack 3.
    ans += a[3] / 4;
    a[3] %= 4;
    if (a[3] > 0) {
      ans++;
      int num2 = (4 - a[3]) * 2 - 1;
      if (a[2] > num2) {
        a[2] -= num2;
        a[1] = max(0, a[1] - (36 - a[3] * 9 - num2 * 4));
      } else {
        a[1] = max(0, a[1] - (36 - a[3] * 9 - a[2] * 4));
        a[2] = 0;
      }
    }
    // Pack 2.
    ans += a[2] / 9;
    a[2] %= 9;
    if (a[2] > 0) {
      ans++;
      a[1] = max(0, a[1] - (36 - a[2] * 4));
    }
    ans += (a[1] + 35) / 36;
    cout << ans << endl;
  }
  return 0;
}
