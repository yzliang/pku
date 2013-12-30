#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int sign(double);

struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  bool operator<(const Point& that) const {
    int cmp = sign(x - that.x);
    return cmp != 0 ? cmp == -1 : sign(y - that.y) == -1;
  }
};

int n, m;
Point wall[30][2];
vector<Point> g;

void create_exteriors() {
  bool touch[101][101] = {0};
  for (int i = 0; i < n; i++) {
    touch[(int)wall[i][0].x][(int)wall[i][0].y] = true;
    touch[(int)wall[i][1].x][(int)wall[i][1].y] = true;
  }
  int l0 = 0, l1 = 0, l2 = 0, l3 = 0;
  for (int i = 0; i < 100; i++) {
    if (touch[i][0]) {
      g.push_back(Point((i + l0) / 2.0, 0));
      l0 = i;
    }
    if (touch[i][100]) {
      g.push_back(Point((i + l1) / 2.0, 100));
      l1 = i;
    }
    if (touch[0][i]) {
      g.push_back(Point(0, (i + l2) / 2.0));
      l2 = i;
    }
    if (touch[100][i]) {
      g.push_back(Point(100, (i + l3) / 2.0));
      l3 = i;
    }
  }
  g.push_back(Point((l0 + 100) / 2.0, 0));
  g.push_back(Point((l1 + 100) / 2.0, 100));
  g.push_back(Point(0, (l2 + 100) / 2.0));
  g.push_back(Point(100, (l3 + 100) / 2.0));
  m = g.size();
}

double cross_product(const Point& p0, const Point& p1, const Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

int sign(double x) {
  if (fabs(x) < 1e-6)
    return 0;
  else
    return x < 0 ? -1 : 1;
}

bool is_cross(const Point& a, const Point& b, const Point& c,
    const Point& d, Point& cp) {
  double s1, s2, s3, s4;
  int d1, d2, d3, d4;
  d1 = sign(s1 = cross_product(a, b, c));
  d2 = sign(s2 = cross_product(a, b, d));
  d3 = sign(s3 = cross_product(c, d, a));
  d4 = sign(s4 = cross_product(c, d, b));
  if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) {
    cp.x = (c.x * s2 - d.x * s1) / (s2 - s1);
    cp.y = (c.y * s2 - d.y * s1) / (s2 - s1);
    return true;
  } else
    return false;
}

Point mid_point(const Point& p0, const Point& p1) {
  return Point((p0.x + p1.x) / 2, (p0.y + p1.y) / 2);
}

void create_interiors() {
  for (int i = 0; i < n; i++) {
    sort(wall[i], wall[i] + 2);
    vector<Point> points;
    Point cp;
    for (int j = 0; j < n; j++) {
      if (i != j && is_cross(wall[i][0], wall[i][1], wall[j][0], wall[j][1],
            cp))
        points.push_back(cp);
    }
    sort(points.begin(), points.end());
    if (points.empty()) {
      g.push_back(mid_point(wall[i][0], wall[i][1]));
    } else {
      g.push_back(mid_point(wall[i][0], points.front()));
      for (int i = 0; i < points.size() - 1; i++)
        g.push_back(mid_point(points[i], points[i + 1]));
      g.push_back(mid_point(points.back(), wall[i][1]));
    }
  }
}

bool blocked(int a, int b) {
  Point dummy;
  for (int i = 0; i < n; i++) {
    if (is_cross(g[a], g[b], wall[i][0], wall[i][1], dummy))
      return true;
  }
  return false;
}

int compute() {
  vector<bool> go(g.size());
  queue<pair<int, int> > q;
  go[0] = true;
  q.push(make_pair(0, 0));
  while (!q.empty()) {
    int head = q.front().first;
    int dis = q.front().second;
    q.pop();
    for (int i = 1; i < g.size(); i++) {
      if (go[i] || blocked(head, i)) continue;
      if (i < m) return dis + 1;
      go[i] = true;
      q.push(make_pair(i, dis + 1));
    }
  }
  return -1;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> wall[i][0].x >> wall[i][0].y >> wall[i][1].x >> wall[i][1].y;
  double x, y;
  cin >> x >> y;
  g.push_back(Point(x, y));
  create_exteriors();
  create_interiors();
  cout << "Number of doors = " << compute() << endl;
  return 0;
}
