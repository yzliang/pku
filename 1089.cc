#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Interval {
  int a, b;
  Interval(int a, int b) : a(a), b(b) {}
  bool operator<(const Interval& that) const {
    if (a != that.a)
      return a < that.a;
    else
      return b <= that.b;
  }
};

int n;
vector<Interval> ints;

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    ints.push_back(Interval(a, b));
  }
  sort(ints.begin(), ints.end());
  int i = 0;
  while (i < ints.size()) {
    Interval merged = ints[i];
    int j = i + 1;
    while (j < ints.size() && merged.b >= ints[j].a) {
      merged.b = max(merged.b, ints[j].b);
      j++;
    }
    cout << merged.a << ' ' << merged.b << endl;
    i = j;
  }
  return 0;
}
