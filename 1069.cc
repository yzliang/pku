#include <cstring>
#include <iostream>
using namespace std;

int s, n, h;
bool length[26];
int l[10];
bool can[50][100];
int a[51], b[51];  // a[i] <= col < b[i] for the i-th row.

void set_bound() {
  memset(can, false, sizeof(can));
  int width = s * 2 + 1;
  for (int i = 0; i < s; i++) {
    a[i] = 0;
    b[i] = width;
    for (int j = a[i]; j < b[i]; j++)
      can[i][j] = true;
    width += 2;
  }
  int left = 1;
  for (int i = 0; i < s; i++) {
    a[s + i] = left;
    b[s + i] = 4 * s;
    for (int j = a[s + i]; j < b[s + i]; j++)
      can[s + i][j] = true;
    left += 2;
  }
}

bool can_extend1(int r, int c, int len) {
  if (c + len * 2 >= b[r] || r + len >= h) return false;
  for (int i = 0; i < len; i++)
    if (!can[r + i][c + len * 2] || !can[r + i][c + len * 2 - 1])
      return false;
  return can[r + len][c + len * 2];
}

bool can_extend2(int r, int c, int len) {
  if (r + len >= h || c + len * 2 >= b[r + len]) return false;
  for (int i = 0; i <= len * 2; i++)
    if (!can[r + len][c + i]) return false;
  return true;
}

bool fill(int r, int c) {
  // Last row ?
  if (r == h) return true;
  // Out of boundary ?
  if (c >= b[r]) return fill(r + 1, a[r + 1]);
  // Already filled ? (low[y] >= x for sure!!)
  if (!can[r][c]) return fill(r, c + 1);
  // Two patterns.
  if (c % 2) {
    int len = 1, next = 0;
    can[r][c] = false;
    while (next < n) {
      if (len == l[next]) {
        if (fill(r, c + 1)) return true;
        next++;
        continue;
      }
      // Extend the triangle.
      if (can_extend1(r, c, len)) {
        for (int i = 0; i < len; i++)
          can[r + i][c + len * 2] = can[r + i][c + len * 2 - 1] = false;
        can[r + len][c + len * 2] = false;
        len++;
      } else
        break;
    }
    // Backtracking: clear the filled area.
    for (int i = 0; i < len; i++)
      memset(&can[r + i][c + 2 * i], true, (len - i) * 2 - 1);
  } else {
    int len = 1, next = 0;
    can[r][c] = false;
    while (next < n) {
      if (len == l[next]) {
        if (fill(r, c + 1)) return true;
        next++;
        continue;
      }
      // Extend the triangle.
      if (can_extend2(r, c, len)) {
        memset(&can[r + len][c], false, len * 2 + 1);
        len++;
      } else 
        break;
    }
    // Backtracking.
    for (int i = 0; i < len; i++)
      memset(&can[r + i][c], true, i * 2 + 1);
  }
  return false;
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> s >> n;
    h = 2 * s;
    memset(length, false, sizeof(length));
    for (int i = 0; i < n; i++) {
      int len;
      cin >> len;
      length[len] = true;
    }
    int n = 0;
    bool div_s = false;
    for (int i = 1; i <= 25; i++) {
      if (!length[i]) continue;
      if (s % i == 0) div_s = true;
      bool div = false;
      for (int j = 1; j < i; j++)
        if (i % j == 0 && length[j])
          div = true;
      if (!div) l[n++] = i;
    }
    if (div_s) {
      cout << "YES" << endl;
      continue;
    }
    set_bound();
    cout << (fill(0, 0) ? "YES" : "NO") << endl;
  }
  return 0;
}
