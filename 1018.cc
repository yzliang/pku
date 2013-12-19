#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

int n, m[100];
int p[100][100], b[100][100];
int f[100][100][100];

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> m[i];
      for (int j = 0; j < m[i]; j++)
        cin >> b[i][j] >> p[i][j];
    }
    memset(f, 0, sizeof(f));
    for (int i = 0; i < m[0]; i++)
      f[0][0][i] = p[0][i];
    for (int i = 0; i < n - 1; i++)
      for (int j = 0; j <= i; j++)
        for (int k = 0; k < m[j]; k++) {
          if (f[i][j][k] == 0) continue;
          for (int l = 0; l < m[i + 1]; l++)
            if (b[i + 1][l] <= b[j][k]) {
              if (f[i + 1][i + 1][l] == 0 ||
                  f[i + 1][i + 1][l] > f[i][j][k] + p[i + 1][l])
                f[i + 1][i + 1][l] = f[i][j][k] + p[i + 1][l];
            } else {
              if (f[i + 1][j][k] == 0 ||
                  f[i + 1][j][k] > f[i][j][k] + p[i + 1][l])
                f[i + 1][j][k] = f[i][j][k] + p[i + 1][l];
            }
        }
    double ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m[i]; j++)
        if (f[n - 1][i][j] != 0) {
          ans = max(ans, (double) b[i][j] / f[n - 1][i][j]);
        }
    cout << fixed << setprecision(3) << ans << endl;
  }
}
