#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int n;

struct Rect {
  double x1, y1, x2, y2;
} rect[100];

vector<double> xs;
vector<double> ys;

int main() {
  int id = 0;
  while (cin >> n && n > 0) {
    for (int i = 0; i < n; ++i) {
      cin >> rect[i].x1 >> rect[i].y1 >> rect[i].x2 >> rect[i].y2;
      xs.push_back(rect[i].x1);
      xs.push_back(rect[i].x2);
      ys.push_back(rect[i].y1);
      ys.push_back(rect[i].y2);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    
    double ans = 0;
    for (int i = 1; i < xs.size(); ++i) {
      for (int j = 1; j < ys.size(); ++j) {
        if (xs[i] - xs[i - 1] <= 1e-7 || ys[j] - ys[j - 1] <= 1e-7)
          continue;
        for (int k = 0; k < n; ++k) {
          if (xs[i - 1] >= rect[k].x1 && xs[i] <= rect[k].x2 &&
              ys[j - 1] >= rect[k].y1 && ys[j] <= rect[k].y2) {
            ans += (xs[i] - xs[i - 1]) * (ys[j] - ys[j - 1]);
            break;
          }
        }
      }
    }
    cout << "Test case #" << ++id << endl;
    cout << "Total explored area: " << fixed << setprecision(2) << ans << endl;
    cout << endl;
  }
  return 0;
}
