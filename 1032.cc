#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  int k = floor((-5 + sqrt(25.0 - 4 * (4 - 2 * n))) / 2);
  int rest = n - (4 + k) * (k + 1) / 2;
  for (int i = 0; i < k; i++) {
    if (i < k - rest + 1)
      cout << i + 2 << ' ';
    else
      cout << i + 3 << ' ';
  }
  if (rest == 0)
    cout << k + 2 << endl;
  else if (rest <= k + 1)
    cout << k + 3 << endl;
  else
    cout << k + 4 << endl;
  return 0;
}
