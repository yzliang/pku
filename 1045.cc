#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  double vs, r, c, w;
  int n;
  cin >> vs >> r >> c >> n;
  for (int i = 0; i < n; i++) {
    cin >> w;
    double a = r * c * w;
    cout << fixed << setprecision(3) << vs * a / sqrt(1 + a * a) << endl;
  }
  return 0;
}
