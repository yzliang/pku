#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;

struct Point {
  double x, y;
};

int n;
Point p[20][2];

int sign(double x) {
  if (abs(x) < 1e-6) return 0;
  return x > 0 ? 1 : -1;
}

double cross_product(Point& p0, Point& p1, Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

double cross_x(Point& p1, Point& p2, Point& p3, Point& p4) {
  double k = cross_product(p3, p1, p4) /
    ((p4.x - p3.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p4.y - p3.y));
  return p1.x + k * (p2.x - p1.x);
}

double reach(int l, int id1, int r, int id2) {
  Point p1 = p[l][id1], p2 = p[r][id2];
  // Check from entry to p1.
  for (int i = 0; i < r; i++) {
    if ((sign(cross_product(p2, p1, p[i][0])) ^
          sign(cross_product(p2, p1, p[i][1]))) == 0)
      return p[0][0].x;
  }
  // Find the end point.
  for (int i = r + 1; i < n; i++) {
    int s1 = sign(cross_product(p1, p2, p[i][0]));
    int s2 = sign(cross_product(p1, p2, p[i][1]));
    if ((s1 ^ s2) == 0) {
      if (s1 > 0)
        return cross_x(p1, p2, p[i - 1][1], p[i][1]);
      else
        return cross_x(p1, p2, p[i - 1][0], p[i][0]);
    }
  }
  return p[n - 1][0].x;
}

void solve() {
  double ans = p[0][0].x;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      ans = max(ans, reach(i, 0, j, 1));
      ans = max(ans, reach(i, 1, j, 0));
      if (sign(ans - p[n - 1][0].x) == 0) {
        cout << "Through all the pipe." << endl;
        return;
      }
    }
  }
  cout << ans << endl;
}

int main() {
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2);
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; i++) {
      cin >> p[i][0].x >> p[i][0].y;
      p[i][1] = p[i][0];
      p[i][1].y -= 1;
    }
    solve();
  }
  return 0;
}
