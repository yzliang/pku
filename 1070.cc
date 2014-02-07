#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
  double x, y;
  Point(): x(0), y(0) {}
  Point(double x, double y) : x(x), y(y) {}
  Point operator-(const Point& that) const {
    return Point(x - that.x, y - that.y);
  }
};

const double PI = 3.1415926535897932;

int n, m;
Point poly[10], g;
vector<Point> hills;  // [hill[0], hill[1]), ..., [hill[m-1], hill[m])

// Left/right touch points.
Point lp, rp;
int lv, lh, rv, rh;  

void swap(Point& p1, Point& p2) {
  Point temp = p1;
  p1 = p2;
  p2 = temp;
}

inline int next(int x, int n) {
  return (x + 1) % n;
}

inline int prev(int x, int n) {
  return (x + n - 1) % n;
}

void get_hills() {
  hills.clear();
  vector<pair<double, double> > pairs;
  double l, s;
  while (cin >> l >> s) {
    pairs.push_back(make_pair(l, s));
    if (s == 0) break;
  }
  double x, y;
  cin >> x >> y;
  hills.push_back(Point(x, y));
  for (int i = 0; i < pairs.size(); i++) {
    l = pairs[i].first;
    s = pairs[i].second;
    x -= l / sqrt(s * s + 1);
    y -= l / sqrt(1 + 1 / s / s);
    hills.push_back(Point(x, y));
  }
  reverse(hills.begin(), hills.end());
}

double cross_product(const Point& p0, const Point& p1, const Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

double dot_product(const Point& p1, const Point& p2) {
  return p1.x * p2.x + p1.y * p2.y;
}

int sign(double x) {
  if (fabs(x) < 1e-5) return 0;
  return x > 0 ? 1 : -1;
}

double dis(const Point& p1, const Point& p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool counter_clockwise(const Point& p1, const Point& p2) {
  int s = sign(cross_product(poly[0], p1, p2));
  if (s != 0) return s == 1;
  return dis(poly[0], p1) < dis(poly[0], p2);
}

void get_polygon() {
  for (int i = 1; i < n; i++) {
    if (poly[i].y < poly[0].y ||
        (poly[i].y == poly[0].y && poly[i].x < poly[0].x))
      swap(poly[0], poly[i]);
  }
  sort(poly + 1, poly + n, counter_clockwise);
  if (n <= 3) return;
  int i = n - 2;
  while (i > 0 && sign(cross_product(poly[0], poly[n - 1], poly[i])) == 0)
    i--;
  if (i > 0) reverse(poly + i + 1, poly + n);
}

// If point p3 is on segment (p1, p2].
bool on_segment(const Point& p1, const Point& p2, const Point& p3) {
  if (sign(cross_product(p1, p2, p3)) != 0) return false;
  int s = sign(dot_product(Point(p1.x - p3.x, p1.y - p3.y),
        Point(p2.x - p3.x, p2.y - p3.y)));
  if (s == -1) return true;
  if (s == 1) return false;
  // Last case: p3 coincides with p1 or p2.
  return fabs(p3.x - p2.x) < 1e-5 && fabs(p3.y - p2.y) < 1e-5;
}

void touch_init() {
  // Find the leftmost touched hill.
  lv = -1;
  for (lh = 0; lh < m; lh++) {
    for (int i = 0; i < n; i++) {
      if (on_segment(hills[lh], hills[lh + 1], poly[i])) {
        lv = i;
        break;
      }
    }
    if (lv != -1) break;
  }
  // Find the rightmost touched hill.
  rv = -1;
  for (rh = m - 1; rh >= 0; rh--) {
    for (int i = n - 1; i >= 0; i--) {
      if (on_segment(hills[rh], hills[rh + 1], poly[i])) {
        rv = i;
        break;
      }
    }
    if (rv != -1) break;
  }
}

double point_to_line(const Point& p0, const Point& p1, const Point& p2) {
  return fabs(cross_product(p0, p1, p2)) / dis(p1, p2);
}

double get_angle(const Point& v1, const Point& v2) {
  Point origin;
  double val = dot_product(v1, v2) / (dis(v1, origin) * dis(v2, origin));
  if (val > 1)
    return 0;
  else if (val < -1)
    return PI;
  else
    return acos(val);
}

double find_left_angle(const Point& p, int& hill) {
  double len = dis(p, poly[lv]);
  // find the exact hill that this length can lie on.
  int l = 0, r = lh - 1;
  while (l <= r) {
    int mid = l + (r - l) / 2;
    double m_len = dis(hills[mid + 1], lp);
    if (sign(len - m_len) < 0)
      l = mid + 1;
    else
      r = mid - 1;
  }
  hill = l;
  double a1;
  if (lv != rv)
    a1 = get_angle(poly[rv] - poly[lv], p - poly[lv]);
  else
    a1 = get_angle(hills[lh + 1] - hills[lh], p - poly[lv]);
  double a2 = get_angle(hills[lh + 1] - hills[lh], hills[l + 1] - hills[l]);
  double a3 = asin(point_to_line(lp, hills[l], hills[l + 1]) / len);
  return PI - a1 - (a2 - a3);
}

double find_right_angle(const Point& p, int& hill) {
  double len = dis(p, poly[rv]);
  // find the exact hill that this length can lie on.
  int l = rh, r = m - 1;
  while (l <= r) {
    int mid = l + (r - l) / 2;
    double m_len = dis(hills[mid + 1], rp);
    if (sign(len - m_len) > 0)
      l = mid + 1;
    else
      r = mid - 1;
  }
  hill = l;
  double a1;
  if (lv != rv)
    a1 = get_angle(poly[lv] - poly[rv], p - poly[rv]);
  else
    a1 = get_angle(hills[rh] - hills[rh + 1], p - poly[rv]);
  double a2 = get_angle(hills[rh] - hills[rh + 1], hills[l] - hills[l + 1]);
  double a3 = asin(point_to_line(rp, hills[l], hills[l + 1]) / len);
  return PI - a1 - (a2 - a3);
}

void turn_left() {
  double angle;
  int tv = -1, th;
  for (int i = prev(lv, n); i != lv; i = prev(i, n)) {
    int hill;
    double max_angle = find_left_angle(poly[i], hill);
    // Choose the smaller angle.
    if (tv == -1 || sign(max_angle - angle) <= 0) {
      tv = i;
      th = hill;
      angle = max_angle;
    }
  }
  // Rotate and update.
  rp = lp;
  rh = lh;
  rv = lv;
  double len = dis(poly[lv], poly[tv]);
  Point dh = hills[th + 1] - hills[th];
  Point dp = hills[th] - lp;
  double a = dh.x * dh.x + dh.y * dh.y;
  double b = 2 * dh.x * dp.x + 2 * dh.y * dp.y;
  double c = dp.x * dp.x + dp.y * dp.y - len * len;
  double k = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;
  lp.x = hills[th].x + k * dh.x;
  lp.y = hills[th].y + k * dh.y;
  lv = tv;
  lh = th;
}

void turn_right() {
  double angle;
  int tv = -1, th;
  for (int i = next(rv, n); i != lv; i = next(i, n)) {
    int hill;
    double max_angle = find_right_angle(poly[i], hill);
    // Choose the smaller angle.
    if (tv == -1 || sign(max_angle - angle) <= 0) {
      tv = i;
      th = hill;
      angle = max_angle;
    }
  }
  // Rotate and update.
  lp = rp;
  lh = rh;
  lv = rv;
  double len = dis(poly[rv], poly[tv]);
  Point dh = hills[th + 1] - hills[th];
  Point dp = hills[th] - lp;
  double a = dh.x * dh.x + dh.y * dh.y;
  double b = 2 * dh.x * dp.x + 2 * dh.y * dp.y;
  double c = dp.x * dp.x + dp.y * dp.y - len * len;
  double k = (-b + sqrt(b * b - 4 * a * c)) / 2 / a;
  rp.x = hills[th].x + k * dh.x;
  rp.y = hills[th].y + k * dh.y;
  rv = tv;
  rh = th;
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> poly[i].x >> poly[i].y;
    cin >> g.x >> g.y;
    get_hills();
    m = hills.size() - 1;
    // Sort vertices in counter-clockwise order and unique.
    get_polygon();
    // Find the initial touch points.
    touch_init();
    lp = poly[lv];
    rp = poly[rv];
    // Roll and roll.
    while (true) {
      int s;
      if (lv == rv)
        s = sign(g.x - lp.x);
      else {
        double a1 = get_angle(poly[rv] - poly[lv], g - poly[lv]);
        double b1 = get_angle(rp - lp, Point(0, 1));
        double a2 = get_angle(poly[lv] - poly[rv], g - poly[rv]);
        double b2 = get_angle(lp - rp, Point(0, 1));
        if (sign(a1 - b1) == 1)
          s = -1;
        else if (sign(a2 - b2) == 1)
          s = 1;
        else
          s = 0;
      }
      if (s == -1) {
        turn_left();
      } else if (s == 1) {
        turn_right();
      } else
        break;
    }
    // Get the real g-point.
    double l1 = dis(g, poly[lv]);
    double base = dis(poly[lv], poly[rv]);
    double k = l1 / base;
    Point dp = rp - lp;
    double x0 = k * dp.x, y0 = k * dp.y;
    double a = get_angle(poly[rv] - poly[lv], g - poly[lv]);
    g.x = lp.x + x0 * cos(a) - y0 * sin(a);
    g.y = lp.y + x0 * sin(a) + y0 * cos(a);
    cout << fixed << setprecision(3) << g.x << ' ' << g.y << endl;
  }
  return 0;
}
