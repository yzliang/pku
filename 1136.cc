#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

struct Point {
  int x, y;
  Point(): x(0), y(0) {}
  Point(int x, int y): x(x), y(y) {}
  bool operator==(const Point& that) const {
    return x == that.x && y == that.y;
  }
};

const double PI = 3.1415926535897932;

int n;
double r;
Point p[500];
Point c;

double dis(Point& p1, Point& p2) {
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  return sqrt(dx * dx + dy * dy);
}

inline bool EQ(double a, double b) {
  return fabs(a - b) < 1e-5;
}

int main() {
  int id = 1;
  while (cin >> n >> r) {
    if (r == 0)
      break;
    for (int i = 0; i < n; i++)
      cin >> p[i].x >> p[i].y;
    // Init.
    c.x = c.y = 0;
    double len = 0;
    double a1 = PI;
    while (true) {
      // Compute the upper bound.
      double max_delta = 2 * PI;
      if (-c.y + 1e-5 < r) {
        double a2 = asin(-c.y / r);
        max_delta = a2 - a1;
        if (max_delta < -1e-5)
          max_delta += 2 * PI;
      }
      // Find the next center.
      Point nc;
      double min_delta = 2 * PI;
      for (int i = 0; i < n; i++) {
        if (p[i].y > 0) continue;
        if (dis(c, p[i]) > r + 1e-5) continue;
        if (c == p[i]) continue;
        // Compute the angle.
        double a2;
        if (p[i].y > c.y)
          a2 = acos((p[i].x - c.x) / dis(p[i], c));
        else if (p[i].y == c.y)
          a2 = p[i].x > c.x ? 0 : PI;
        else
          a2 = 2 * PI - acos((p[i].x - c.x) / dis(p[i], c));
        double delta = a2 - a1;
        if (delta < -1e-5)
          delta += 2 * PI;
        // Update.
        if (delta <= max_delta) {
          if (EQ(delta, min_delta)) {
            if (dis(p[i], c) > dis(nc, c)) {
              min_delta = delta;
              nc = p[i];
            }
          } else if (delta < min_delta) {
            min_delta = delta;
            nc = p[i];
          }
        }
      }
      if (EQ(min_delta, 2 * PI)) {
        if (EQ(max_delta, 2 * PI))
          len = PI * r;
        else
          len += max_delta * r;
        break;
      } else {
        len += min_delta * r;
        r -= dis(nc, c);
        a1 += min_delta;
        if (a1 >= 2 * PI)
          a1 -= 2 * PI;
        c = nc;
      }
    }
    cout << "Pendulum #" << id++ << endl;
    cout << "Length of periodic orbit = ";
    cout << fixed << setprecision(2) << len * 2 << endl << endl;
  }
  return 0;
}
