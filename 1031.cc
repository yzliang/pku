#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

struct Point {
  double x, y;
};

double k, h;
int n;
Point origin;
Point p[200], q[200];
const double PI = 3.1415926535897932384626;

int sign(double x) {
  if (fabs(x) < 1e-6)
    return 0;
  return x > 0 ? 1 : -1;
}

bool compare_angle(const Point& p1, const Point& p2) {
  return atan2(p1.y, p1.x) < atan2(p2.y, p2.x);
}

double cross_product(Point& p0, Point& p1, Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

int main() {
  cin >> k >> h >> n;
  for (int i = 0; i < n; i++)
    cin >> p[i].x >> p[i].y;
  memcpy(q, p, sizeof(q));
  q[n] = q[0];
  sort(p, p + n, compare_angle);
  p[n] = p[0];
  double sum = 2 * PI;
  for (int i = 0; i < n; i++) {
    double a1 = atan2(p[i].y, p[i].x);
    double a2 = atan2(p[i + 1].y, p[i + 1].x);
    double delta = (i < n - 1) ? a2 - a1 : a2 + 2 * PI - a1;
    if (delta < 1e-6) continue;
    if (delta >= PI) {
      sum -= delta;
      break;
    }
    Point mid = {(p[i].x + p[i + 1].x) / 2, (p[i].y + p[i + 1].y) / 2};
    bool cover = false;
    for (int j = 0; j < n; j++) {
      double cp1 = cross_product(origin, mid, q[j]);
      double cp2 = cross_product(origin, mid, q[j + 1]);
      if ((sign(cp1) ^ sign(cp2)) != -2) continue;
      Point& positive = cp1 > 0 ? q[j] : q[j + 1];
      Point& negative = cp1 > 0 ? q[j + 1] : q[j];
      if (sign(cross_product(positive, negative, origin)) == 1)
        continue;
      cover = true;
      break;
    }
    if (!cover) {
      sum -= delta;
      break;
    }
  }
  cout << fixed << setprecision(2) << sum * k * h << endl;
  return 0;
}
