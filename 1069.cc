#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int s, n, h;
int l[10];
int low[100];  // first(lowest) row of a column that is empty (initial: 0).
int a[50], b[50];  // a[i] <= col < b[i] for the i-th row.
int c[100];  // row < c[i] for the i-th column.

void set_bound() {
  memset(low, 0, sizeof(low));
  int width = s * 2 + 1;
  for (int i = 0; i < s; i++) {
    a[i] = 0;
    b[i] = width;
    c[width - 1] = c[width - 2] = 2 * s;
    low[width - 1] = low[width - 2] = i;
    width += 2;
  }
  c[0] = s;
  c[4 * s - 1] = 2 * s;
  low[4 * s - 1] = s;
  int left = 1;
  for (int i = 0; i < s; i++) {
    a[i] = left;
    b[i] = 4 * s;
    c[left] = c[left + 1] = s + i + 1;
    left += 2;
  }
}

bool fill(int x, int y) {
  // Last row ?
  if (x == h) return true;
  // Out of boundary ?
  if (y >= b[x]) return fill(x + 1, a[x + 1]);
  // Already filled ? (low[y] >= x for sure!!)
  if (low[y] > x) return fill(x, y + 1);

  // Try two kinds of triangles.
  if (y & 1) {
  } else {
    int len = 1, next = 0;
    low[y]++;
    while (next < n) {
      if (len == l[next]) {
        if (fill(x, y + 1)) return true;
        next++;
      } else if (x + len < h && low[y + len * 2 - 1] == x + len &&
                 low[y + len * 2] == x + len) {
        low[y + len * 2 - 1]++;
        low[y + len * 2]++;
        len++;
      } else
        break;
    }
    // Backtracking.
    while (len > 1) {
      len--;
      low[y + len * 2]--;
      low[y + len * 2 - 1]--;
    }
    low[y--];
  }
  return false;
}

int main() {
  int t;
  for (; t > 0; t--) {
    cin >> s >> n;
    h = 2 * s;
    for (int i = 0; i < n; i++)
      cin >> l[i];
    sort(l, l + n);
    set_bound();
    cout << (fill(0, 0) ? "YES" : "NO") << endl;
  }
  return 0;
}
