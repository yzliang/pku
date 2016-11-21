// DFS.
#include <iostream>
using namespace std;

int r, c;
char board[20][21];

void ReadData() {
  cin >> r >> c;
  for (int i = 0; i < r; ++i)
    cin >> board[i];
}

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

void Search(int x, int y, int len, int* ans, bool visited[]) {
  visited[board[y][x] - 'A'] = true;
  if (len > *ans) {
    *ans = len;
  }
  for (int i = 0; i < 4; ++i) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 0 && nx < c && ny >= 0 && ny < r &&
        !visited[board[ny][nx] - 'A']) {
      Search(nx, ny, len + 1, ans, visited);
    }
  }
  visited[board[y][x] - 'A'] = false;
}

void Solve() {
  int ans = 0;
  bool visited[26] = {false};
  Search(0, 0, 1, &ans, visited);
  cout << ans << endl;
}

int main() {
  ReadData();
  Solve();
  return 0;
}
