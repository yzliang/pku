#include <cstring>
#include <iostream>
#include <stdint.h>
using namespace std;

int n, k;
int64_t c;
int64_t f[21][21][2];
bool used[21];
int ans[21];

void solve(int i, int64_t c) {
  if (i == 1) {
    int n1, n2;
    bool stop = false;
    for (n1 = 1; n1 <= n; n1++) {
      for (n2 = 1; n2 <= n; n2++) {
        if (n1 == n2) continue;
        int64_t total = n1 < n2 ? f[n - 1][n2 - 1][1] : f[n - 1][n2][0];
        if (total >= c) {
          stop = true;
          break;
        }
        c -= total;
      }
      if (stop) break;
    }
    ans[1] = n1;
    ans[2] = n2;
    used[n1] = used[n2] = true;
    solve(3, c);
  } else if (i < n) {
    bool up = ans[i - 1] < ans[i - 2];
    int num = 0;
    for (int j = 1; j <= n - i + 1; j++) {
      for (num++; used[num]; num++);
      if (up && num < ans[i - 1]) continue;
      if (!up && num > ans[i - 1]) continue;
      int64_t total = up ? f[n - i + 1][j][1] : f[n - i + 1][j][0];
      if (total >= c) {
        ans[i] = num;
        used[num] = true;
        break;
      }
      c -= total;
    }
    solve(i + 1, c);
  } else if (i == n) {
    for (int j = 1; j <= n; j++) {
      if (!used[j]) {
        ans[i] = j;
        break;
      }
    }
  }
}

int main() {
  f[1][1][0] = f[1][1][1] = 1;
  for (int i = 2; i <= 20; i++) {
    for (int j = 1; j <= i; j++) {
      for (int k = 1; k < j; k++)
        f[i][j][1] += f[i - 1][k][0];
      for (int k = j + 1; k <= i; k++)
        f[i][j][0] += f[i - 1][k - 1][1];
    }
  }
  cin >> k;
  for (int i = 0; i < k; i++) {
    cin >> n >> c;
    memset(used, 0, sizeof(used));
    if (n >= 2)
      solve(1, c);
    else
      ans[1] = 1;
    cout << ans[1];
    for (int j = 2; j <= n; j++)
      cout << ' ' << ans[j];
    cout << endl;
  }
  return 0;
}
