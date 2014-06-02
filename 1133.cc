#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

const double PI = 3.1415926535897932;

struct Point {
  int x, y;

  Point() {}
  Point(int x, int y) : x(x), y(y) {}

  bool operator<(const Point& that) const {
    if (x != that.x)
      return x < that.x;
    else
      return y < that.y;
  }

  Point operator-(const Point& that) {
    return Point(x - that.x, y - that.y);
  }
};

typedef map<Point, int> SMAP;

int n, m;
Point stars[1000];
SMAP smap;
int b[1000];
int num[50];
char name[50][41];
Point con[50][1000];

int square_dis(const Point& p) {
  return p.x * p.x + p.y * p.y;
}

double distance(const Point& p) {
  return sqrt(square_dis(p));
}

int dot_product(const Point& v1, const Point& v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

int cross_product(const Point& v1, const Point& v2) {
  return v1.x * v2.y - v2.x * v1.y;
}

int sign(int x) {
  if (x != 0)
    return x > 0 ? 1 : -1;
  else
    return 0;
}

// Angle from v1 to v2.
double get_angle(const Point& v1, const Point& v2) {
  double d1 = distance(v1), d2 = distance(v2);
  double val = dot_product(v1, v2) / d1 / d2;
  double angle;
  if (val > 1)
    angle = 0;
  else if (val < -1)
    angle = PI;
  else
    angle = acos(val);
  // Counter-clockwise is positive!
  int s = sign(cross_product(v1, v2));
  if (s != 0)
    return angle * s;
  else
    return angle;
}

bool add_point(SMAP& smap, double x, double y, int& id) {
  Point p(round(x), round(y));
  // Are they integral?
  if (abs(x - p.x) > 1e-5 || abs(y - p.y) > 1e-5)
    return false;
  SMAP::iterator it = smap.find(p);
  if (it == smap.end())
    return false;
  id = it->second;
  return true;
}

int get_occurrence(Point* stars, int* b, int n, Point* con, int m, SMAP& smap,
    int* best) {
  static int current[1000];
  if (m == 1) {
    best[0] = 0;
    for (int i = 0; i < n; i++) {
      if (b[i] > b[best[0]])
        best[0] = i;
    }
    return n;
  }
  Point& p0 = con[0];
  Point& p1 = con[1];
  int total = 0, max_bright = 0;
  // Enumerate the positions of the constellation's first two stars.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      Point& pa = stars[i];
      Point& pb = stars[j];
      double angle = get_angle(p1 - p0, pb - pa);
      double scale = distance(pb - pa) / distance(p1 - p0);
      current[0] = i;
      current[1] = j;
      bool valid = true;
      int bright = b[i] + b[j];
      for (int k = 2; k < m; k++) {
        Point delta = con[k] - p0;
        // Scale and translate.
        double x = delta.x * cos(angle) - delta.y * sin(angle);
        double y = delta.y * cos(angle) + delta.x * sin(angle);
        x = pa.x + scale * x;
        y = pa.y + scale * y;
        if (!add_point(smap, x, y, current[k])) {
          valid = false;
          break;
        }
        bright += b[current[k]];
      }
      if (valid) {
        total++;
        if (bright > max_bright) {
          max_bright = bright;
          memcpy(best, current, sizeof(int) * m);
        }
      }
    }
  }
  return total;
}

void process() {
  static int best[1000];
  static int dummy[1000] = {0};
  for (int i = 0; i < m; i++) {
    SMAP con_map;
    for (int j = 0; j < num[i]; j++)
      con_map.insert(make_pair(con[i][j], j));
    // Self-occurrence count.
    int self_occur = get_occurrence(con[i], dummy, num[i], con[i], num[i],
        con_map, best);
    // Real occurrence count.
    int total = get_occurrence(stars, b, n, con[i], num[i], smap, best) /
      self_occur;
    // Output.
    cout << endl;
    cout << name[i] << " occurs " << total << " time(s) in the map.\n";
    if (total > 0) {
      cout << "Brightest occurrence:";
      vector<Point> v;
      for (int j = 0; j < num[i]; j++)
        v.push_back(stars[best[j]]);
      sort(v.begin(), v.end());
      for (int j = 0; j < num[i]; j++)
        cout << " (" << v[j].x << ',' << v[j].y << ')';
      cout << endl;
    }
  }
}

int main() {
  int id = 1;
  while (cin >> n) {
    if (n == 0)
      break;
    smap.clear();
    for (int i = 0; i < n; i++) {
      cin >> stars[i].x >> stars[i].y >> b[i];
      smap.insert(make_pair(stars[i], i));
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
      cin >> num[i] >> name[i];
      for (int j = 0; j < num[i]; j++)
        cin >> con[i][j].x >> con[i][j].y;
    }
    cout << "Map #" << id++ << endl;
    process();
    cout << "-----" << endl;
  }
  return 0;
}
