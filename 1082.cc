#include <iostream>
using namespace std;

bool f[2002][13][32];

int num_days(int y, int m) {
  if (m == 2) {
    if (y % 100 == 0)
      return y % 400 == 0 ? 29 : 28;
    else
      return y % 4 == 0 ? 29 : 28;
  } else if (m == 4 || m == 6 || m == 9 || m == 11)
    return 30;
  else
    return 31;
}

void get_tomorrow(int& y, int& m, int& d) {
  int days = num_days(y, m);
  if (d < days) {
    d++;
    return;
  }
  d = 1;
  if (m == 12) {
    m = 1;
    y++;
  } else
    m++;
}

bool next_month(int& y, int& m, int& d) {
  if (y == 2001 && (m == 11 || (m == 10 && d > 4)))
    return false;
  if (m == 12) {
    y++;
    m = 1;
  } else
    m++;
  return d <= num_days(y, m);
}

void compute() {
  for (int i = 2001; i >= 1900; i--) {
    for (int j = 12; j >= 1; j--) {
      for (int k = 31; k >= 1; k--) {
        if (i == 2001 && (j > 11 || (j == 11 && k >= 4)))
          continue;
        if (k > num_days(i, j)) continue;
        int ny = i, nm = j, nd = k;
        get_tomorrow(ny, nm, nd);
        f[i][j][k] = !f[ny][nm][nd];
        ny = i;
        nm = j;
        nd = k;
        if (next_month(ny, nm, nd))
          f[i][j][k] = f[i][j][k] || !f[ny][nm][nd];
      }
    }
  }
}

int main() {
  compute();
  int t;
  cin >> t;
  for (; t > 0; t--) {
    int y, m, d;
    cin >> y >> m >> d;
    cout << (f[y][m][d] ? "YES" : "NO") << endl;
  }
  return 0;
}
