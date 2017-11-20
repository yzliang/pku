#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

int v, p;
int x[301];

// Sum of left/right/min distances between village i and village j if we are
// to build post-offices at i, or at j, or at both.
int left_dis[301][301], right_dis[301][301], min_dis[301][301];

// Optimal sum for villages 1..j by building i post-offices, with the
// rightmost post-office built at village j.
int f[31][301];

void ReadData() {
  cin >> v >> p;
  for (int i = 1; i <= v; ++i) {
    cin >> x[i];
  }
}

int Solve() {
  // Compute sum of distances.
  for (int i = 1; i <= v; ++i) {
    left_dis[i][i] = 0;
    for (int j = i + 1; j <= v; ++j) {
      left_dis[i][j] = left_dis[i][j - 1] + x[j] - x[i];
    }
    right_dis[i][i] = 0;
    for (int j = i - 1; j >= 1; --j) {
      right_dis[j][i] = right_dis[j + 1][i] + x[i] - x[j];
    }
  }
  for (int i = 1; i <= v; ++i) {
    min_dis[i][i] = 0;
    int mid = i;
    for (int j = i + 1; j <= v; ++j) {
      while (x[mid] - x[i] <= x[j] - x[mid]) {
        ++mid;
      }
      min_dis[i][j] = left_dis[i][mid - 1] + right_dis[mid][j];
    }
  }

  // DP.
  for (int i = 1; i <= p; ++i) {
    for (int j = 1; j <= v; ++j) {
      f[i][j] = INT_MAX;
    }
  }
  for (int i = 1; i <= v; ++i) {
    f[1][i] = right_dis[1][i];
  }
  for (int i = 1; i < p; ++i) {
    for (int j = i; j <= v; ++j) {
      for (int k = j + 1; k <= v; ++k) {
        f[i + 1][k] = min(f[i + 1][k], f[i][j] + min_dis[j][k]);
      }
    }
  }
  int ans = INT_MAX;
  for (int i = p; i <= v; ++i) {
    ans = min(ans, f[p][i] + left_dis[i][v]);
  }
  return ans;
}

int main() {
  ReadData();
  cout << Solve() << endl;
  return 0;
}
