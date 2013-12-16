#include <iostream>
using namespace std;

int n, m;
int p[200], d[200];
int f[21][801];  // max points
int g[21][801];  // id of the last person
int prev[200][21][801];  // id of the previous person

bool read_input() {
  cin >> n >> m;
  if (n == 0) return false;
  for (int i = 0; i < n; i++)
    cin >> p[i] >> d[i];
  return true;
}

void compute() {
  for (int i = 0; i <= m; i++)
    for (int j = 0; j <= 800; j++)
      f[i][j] = -1;
  f[0][400] = 0;
  for (int i = 0; i < n; i++) {
    int delta = p[i] - d[i], sum = p[i] + d[i];
    for (int j = m - 1; j >= 0; j--) {
      for (int k = 0; k <= 800; k++) {
        if (f[j][k] == -1) continue;
        if (f[j + 1][k + delta] == -1 || f[j + 1][k + delta] < f[j][k] + sum) {
          f[j + 1][k + delta] = f[j][k] + sum;
          g[j + 1][k + delta] = i;
          prev[i][j + 1][k + delta] = g[j][k];
        }
      }
    }
  }
}

int main() {
  int t = 0;
  while (read_input()) {
    compute();
    cout << "Jury #" << ++t << endl;
    int i = 0;
    while (true) {
      if (f[m][400 + i] >= 0 || f[m][400 - i] >= 0) {
        if (f[m][400 + i] >= f[m][400 - i])
          i = 400 + i;
        else
          i = 400 - i;
        break;
      }
      i++;
    }
    int candy[21];
    int last = g[m][i];
    int j = m;
    while (j > 0) {
      candy[j] = last;
      last = prev[last][j][i];
      i -= p[candy[j]] - d[candy[j]];
      j--;
    }
    int pro = 0, def = 0;
    for (i = 1; i <= m; i++) {
      pro += p[candy[i]];
      def += d[candy[i]];
    }
    cout << "Best jury has value " << pro << " for prosecution and value "
         << def << " for defence:" << endl;
    for (int i = 1; i <= m; i++)
      cout << ' ' << candy[i] + 1;
    cout << endl << endl;
  }
  return 0;
}
