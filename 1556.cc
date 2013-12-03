#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Wall {
  double x;
  double y[4];
};

int n;
Wall w[18];
double dis[18][4];
const double BIG = 1e10;

bool read_input() {
  cin >> n;
  if (n == -1) return false;
  for (int i = 0; i < n; i++) {
    cin >> w[i].x;
    for (int j = 0; j < 4; j++)
      cin >> w[i].y[j];
  }
  return true;
}

double distance(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int dblcmpl(double x) {
  if (fabs(x) < 1e-6)
    return 0;
  return x > 0 ? 1 : -1;
}

double cross_product(double x0, double y0, double x1, double y1, double x2, double y2) {
  return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
}

bool cross(double x1, double y1, double x2, double y2, double x3, double y3,
           double x4, double y4) {
  return (dblcmpl(cross_product(x1, y1, x2, y2, x3, y3)) ^
      dblcmpl(cross_product(x1, y1, x2, y2, x4, y4))) == -2 &&
      (dblcmpl(cross_product(x3, y3, x4, y4, x1, y1)) ^
       dblcmpl(cross_product(x3, y3, x4, y4, x2, y2))) == -2;
}

void test_and_update(double src_val, double x1, double y1, double x2,
                     double y2, int l, int r, double& val) {
  for (int i = l; i < r; i++) {
    if (cross(x1, y1, x2, y2, w[i].x, 0, w[i].x, w[i].y[0])) return;
    if (cross(x1, y1, x2, y2, w[i].x, w[i].y[1], w[i].x, w[i].y[2])) return;
    if (cross(x1, y1, x2, y2, w[i].x, w[i].y[3], w[i].x, 10)) return;
  }
  val = min(val, src_val + distance(x1, y1, x2, y2));
}

int main() {
  while (read_input()) {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < 4; j++)
        dis[i][j] = BIG;
    double ans = BIG;
    // Go from the initial point.
    for (int i = 0; i < n; i++)
      for (int j = 0; j < 4; j++)
        test_and_update(0, 0, 5, w[i].x, w[i].y[j], 0, i, dis[i][j]);
    test_and_update(0, 0, 5, 10, 5, 0, n, ans);
    // Go from intermediate point.
    if (ans == BIG) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
          test_and_update(dis[i][j], w[i].x, w[i].y[j], 10, 5, i + 1, n, ans);
          for (int k = i + 1; k < n; k++)
            for (int l = 0; l < 4; l++)
              test_and_update(dis[i][j], w[i].x, w[i].y[j], w[k].x, w[k].y[l],
                              i + 1, k, dis[k][l]);
        }
      }
    }
    cout << fixed << setprecision(2) << ans << endl;
  }
  return 0;
}
