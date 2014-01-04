#include <cmath>
#include <iostream>
using namespace std;

const double g1 = (sqrt(5.0) - 1) / 2;
const double g2 = (sqrt(5.0) + 1) / 2;

int main() {
  int a, b;
  while (cin >> a >> b) {
    if (a > b) {
      int temp = a;
      a = b;
      b = temp;
    }
    if (a == 0) {
      cout << (b != 0) << endl;
      continue;
    }
    int k = ceil(a * g1);
    int a0 = k * g2, b0 = a0 + k;
    cout << (a0 != a || b0 != b) << endl;
  }
  return 0;
}
