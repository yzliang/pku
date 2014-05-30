#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

int n;
Point straws[13][2];
bool con[13][13];

int sign(int x) {
  if (x > 0)
    return 1;
  else if (x < 0)
    return -1;
  else
    return 0;
}

int cross_product(Point& p0, Point& p1, Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

bool is_cross(int i, int j) {
  int s1 = sign(cross_product(straws[i][0], straws[i][1], straws[j][0]));
  int s2 = sign(cross_product(straws[i][0], straws[i][1], straws[j][1]));
  int s3 = sign(cross_product(straws[j][0], straws[j][1], straws[i][0]));
  int s4 = sign(cross_product(straws[j][0], straws[j][1], straws[i][1]));
  if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0) {
    // Four points on a line?
    if (straws[i][0].x == straws[i][1].x) {
      // Perpendicular segments?
      if (max(straws[i][0].y, straws[i][1].y) <
          min(straws[j][0].y, straws[j][1].y))
        return false;
      if (max(straws[j][0].y, straws[j][1].y) <
          min(straws[i][0].y, straws[i][1].y))
        return false;
      return true;
    } else {
      if (max(straws[i][0].x, straws[i][1].x) <
          min(straws[j][0].x, straws[j][1].x))
        return false;
      if (max(straws[j][0].x, straws[j][1].x) <
          min(straws[i][0].x, straws[i][1].x))
        return false;
      return true;
    }
  } else
    return s1 * s2 <= 0 && s3 * s4 <= 0;
}

int main() {
  while (cin >> n) {
    if (n == 0)
      break;
    for (int i = 0; i < n; i++)
      cin >> straws[i][0].x >> straws[i][0].y >> straws[i][1].x
          >> straws[i][1].y;
    memset(con, 0, sizeof(con));
    for (int i = 0; i < n; i++)
      con[i][i] = true;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        con[i][j] = con[j][i] = is_cross(i, j);
    // Floyd.
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (!con[i][j] && con[i][k] && con[k][j])
            con[i][j] = con[j][i] = true;
        }
      }
    }
    int a, b;
    while (cin >> a >> b) {
      if (a == 0 && b == 0)
        break;
      cout << (con[a - 1][b - 1] ? "CONNECTED" : "NOT CONNECTED") << endl;
    }
  }
  return 0;
}
