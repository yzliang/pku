#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int l, n, start;
int s[16], sx[16], sy[16];
bool used[16];
int nx[40];  // The next available row of each column.

bool greedy() {
  memset(used, 0, sizeof(used));
  memset(nx, 0, sizeof(nx));
  start = 1;
  while (start < n && s[start] == s[0])
    start++;
  if (start > (l / s[0]) * (l / s[0]))
    return false;
  int row = 0, col = 0;
  for (int i = 0; i < start; i++) {
    used[i] = true;
    if (col >= l) {
      row += s[0];
      col = 0;
    }
    sx[i] = row;
    sy[i] = col;
    for (int j = col; j < col + s[0]; j++)
      nx[j] = row + s[0];
    col += s[0];
  }
  return true;
}

bool search(int x, int y) {
  if (x == l) return true;
  for (int i = start; i < n; i++) {
    if (used[i]) continue;
    // Only try one of the same sizes in the same position.
    if (!used[i - 1] && s[i - 1] == s[i]) continue;
    if (x + s[i] > l || y + s[i] > l) continue;
    bool collide = false;
    for (int j = start; j < n; j++) {
      if (used[j] && x <= sx[j] + s[j] - 1 && x + s[i] - 1 >= sx[j] &&
          y <= sy[j] + s[j] - 1 && y + s[i] - 1 >= sy[j]) {
        collide = true;
        break;
      }
    }
    if (collide) continue;
    used[i] = true;
    sx[i] = x;
    sy[i] = y;
    for (int j = 0; j < s[i]; j++)
      nx[y + j] += s[i];
    int x1 = nx[0], y1 = 0;
    for (int j = 1; j < l; j++) {
      if (nx[j] < x1) {
        x1 = nx[j];
        y1 = j;
      }
    }
    if (search(x1, y1)) return true;
    used[i] = false;
    for (int j = 0; j < s[i]; j++)
      nx[y + j] -= s[i];
  }
  return false;
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> l >> n;
    int area = 0;
    for (int i = 0; i < n; i++) {
      cin >> s[i];
      area += s[i] * s[i];
    }
    if (area != l * l) {
      cout << "HUTUTU!" << endl;
      continue;
    }
    sort(s, s + n, greater<int>());
    if (!greedy()) {
      cout << "HUTUTU!" << endl;
      continue;
    }
    int x0 = nx[0], y0 = 0;
    for (int i = 1; i < l; i++) {
      if (nx[i] < x0) {
        x0 = nx[i];
        y0 = i;
      }
    }
    if (search(x0, y0))
      cout << "KHOOOOB!" << endl;
    else
      cout << "HUTUTU!" << endl;
  }
  return 0;
}
