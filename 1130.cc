#include <iostream>
#include <queue>
using namespace std;

const int MAX_N = 100;
int n, et;
bool pass[MAX_N][MAX_N];
bool visit[MAX_N];
int f[MAX_N];

void dfs(int i) {
  visit[i] = true;
  for (int j = 0; j < n; j++) {
    if (pass[i][j] && !visit[j])
      dfs(j);
  }
  for (int j = 0; j < n; j++) {
    if (!pass[i][j])
      continue;
    else if (j == et) {
      // Direct guard.
      f[i] = i;
      return;
    } else if (f[j] == -1)
      continue;  // No visit.
    else if (f[i] == -1)
      f[i] = f[j];  // First guard.
    else if (f[i] != f[j]) {
      f[i] = i;  // Multiple guards exist.
      return;
    }
  }
}

int main() {
  cin >> n >> et;
  int a, b;
  while (cin >> a >> b)
    pass[a][b] = true;
  for (int i = 0; i < n; i++)
    f[i] = -1;
  dfs(0);
  cout << "Put guards in room " << f[0] << '.' << endl;
  return 0;
}
