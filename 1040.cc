#include <algorithm>
#include <iostream>
using namespace std;

struct Order {
  int l, r;
  int num;
  int value;
  bool operator<(const Order& that) const {
    if (value != that.value)
      return value > that.value;
    else if (num != that.num)
      return num > that.num;
    else if (l != that.l)
      return l < that.l;
    else
      return r < that.r;
  }
};

int cap, n, m;
int best = 0;
Order ord[22];
int rest[23];
int a[7];

void search(int pos, int sum) {
  if (pos == n) {
    best = max(sum, best);
    return;
  }
  if (sum + rest[pos] < best) return;
  // Use current order?
  bool can = true;
  for (int i = ord[pos].l; i < ord[pos].r; i++) {
    if (a[i] + ord[pos].num <= cap) continue;
    can = false;
    break;
  }
  if (can) {
    for (int i = ord[pos].l; i < ord[pos].r; i++)
      a[i] += ord[pos].num;
    search(pos + 1, sum + ord[pos].value);
    for (int i = ord[pos].l; i < ord[pos].r; i++)
      a[i] -= ord[pos].num;
  }
  // Skip current order.
  search(pos + 1, sum);
}

int main() {
  while (cin >> cap >> m >> n) {
    if (cap == 0 && m == 0 && n == 0) break;
    for (int i = 0; i < n; i++) {
      cin >> ord[i].l >> ord[i].r >> ord[i].num;
      ord[i].value = (ord[i].r - ord[i].l) * (ord[i].num);
    }
    sort(ord, ord + n);
    rest[n] = 0;
    for (int i = n - 1; i >= 0; i--)
      rest[i] = rest[i + 1] + ord[i].value;
    best = 0;
    search(0, 0);
    cout << best << endl;
  }
  return 0;
}
