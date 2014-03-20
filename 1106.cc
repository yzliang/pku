#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

int n;
double r;
Point t;
Point ps[1000];
bool in[1000];

int cross_product(Point& p1, Point& p2, Point& p3, Point& p4) {
  return (p2.x - p1.x) * (p4.y - p3.y) - (p4.x - p3.x) * (p2.y - p1.y);
}

int sq_dis(Point& p1, Point& p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int main() {
  while (cin >> t.x >> t.y >> r) {
    if (r < 0) break;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> ps[i].x >> ps[i].y;
      in[i] = sq_dis(ps[i], t) <= r * r;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (!in[i]) continue;
      int total = 0;
      for (int j = 0; j < n; j++) {
        if (in[j] && cross_product(t, ps[i], t, ps[j]) >= 0)
          total++;
      }
      if (total > ans)
        ans = total;
    }
    cout << ans << endl;
  }
  return 0;
}
