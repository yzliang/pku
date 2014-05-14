#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

const double PI = 3.1415926;

int n, l, total;
Point p[1000];
Point hull[1000];

int cross_product(const Point& p0, const Point& p1, const Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

double dis(const Point& p1, const Point& p2) {
  int sqr = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
  return sqrt((double) sqr);
}

bool compare_angle(const Point& p1, const Point& p2) {
  int prod = cross_product(p[0], p1, p2);
  if (prod != 0)
    return prod > 0;
  else
    return dis(p[0], p1) > dis(p[0], p2);
}

void find_hull() {
  // Sort all points according to the lowest one, in counter-clockwise order.
  int low = 0;
  for (int i = 1; i < n; i++) {
    if (p[i].y < p[low].y || (p[i].y == p[low].y && p[i].x < p[low].x))
      low = i;
  }
  if (low != 0) {
    Point temp = p[0];
    p[0] = p[low];
    p[low] = temp;
  }
  sort(p + 1, p + n, compare_angle);
  // Graham scan.
  hull[0] = p[0];
  total = 1;
  for (int i = 1; i < n; i++) {
    // Skip points on the same direction.
    if (i > 1 && cross_product(p[0], p[i - 1], p[i]) == 0)
      continue;
    while (total >= 2 &&
        cross_product(hull[total - 2], hull[total - 1], p[i]) <= 0)
      total--;
    hull[total++] = p[i];
  }
  while (total > 3 &&
      cross_product(hull[total - 2], hull[total - 1], hull[0]) <= 0)
    total--;
}

int compute() {
  find_hull();
  double ans = dis(hull[0], hull[total - 1]);
  for (int i = 0; i < total - 1; i++)
    ans += dis(hull[i], hull[i + 1]);
  ans += 2 * PI * l;
  return round(ans);
}

int main() {
  cin >> n >> l;
  for (int i = 0; i < n; i++)
    cin >> p[i].x >> p[i].y;
  cout << compute() << endl;
  return 0;
}
