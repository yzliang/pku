#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

struct Point {
  int x, y;
  bool operator<(const Point& that) const {
    return that.y != y ? y < that.y : x < that.x;
  }
};

int r, c, n;
Point p[5000];
bool map[5000][5000];

int main() {
  cin >> r >> c >> n;
  for (int i = 0; i < n; i++) {
    cin >> p[i].x >> p[i].y;
    p[i].x--;
    p[i].y--;
    map[p[i].x][p[i].y] = true;
  }
  sort(p, p + n);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int dx = p[j].x - p[i].x, dy = p[j].y - p[i].y;
      // Can p[i] be the first point?
      if (p[i].x - dx >= 0 && p[i].x - dx < r && p[i].y - dy >= 0) continue;
      // Estimate upper bound.
      int max_num = INT_MAX;
      if (dy > 0)
        max_num = (c - 1 - p[i].y) / dy + 1;
      if (dx > 0)
        max_num = min(max_num, (r - 1 - p[i].x) / dx + 1);
      else if (dx < 0)
        max_num = min(max_num, (p[i].x / -dx) + 1);
      if (max_num <= ans) continue;
      max_num = 2;
      int x = p[j].x + dx, y = p[j].y + dy;
      while (x >= 0 && x < r && y < c) {
        if (!map[x][y]) {
          max_num = 0;
          break;
        }
        max_num++;
        x += dx;
        y += dy;
      }
      ans = max(ans, max_num);
    }
  }
  cout << (ans < 3 ? 0 : ans) << endl;
  return 0;
}
