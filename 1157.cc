#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

int f, v;
int a[101][101];
int opt[101][101];

void ReadData() {
  cin >> f >> v;
  for (int i = 1; i <= f; ++i)
    for (int j = 1; j <= v; ++j)
      cin >> a[i][j];
}

int Solve() {
  for (int i = 0; i <= v; ++i)
    opt[0][i] = 0;
  for (int i = 1; i <= f; ++i)
    for (int j = 0; j <= v; ++j)
      opt[i][j] = INT_MIN;
  for (int i = 0; i < f; ++i) {
    for (int j = 0; j < v; ++j) {
      if (opt[i][j] == INT_MIN) continue;
      for (int k = j + 1; k <= v; ++k) {
        opt[i + 1][k] = max(opt[i + 1][k], opt[i][j] + a[i + 1][k]);
      }
    }
  }
  return *max_element(&opt[f][0], &opt[f][0] + v + 1);
}

int main() {
  ReadData();
  cout << Solve() << endl;
  return 0;
}
