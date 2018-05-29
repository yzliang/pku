#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int m, n;
int rooms, max_area;
int wall[50][50];
bool visit[50][50];

const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};

void ReadData() {
  cin >> m >> n;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      cin >> wall[i][j];
}

int Bfs(int x, int y) {
  int area = 0;
  queue<pair<int, int> > nodes; 
  visit[x][y] = true;
  nodes.push(make_pair(x, y));
  while (!nodes.empty()) {
    int cx = nodes.front().first;
    int cy = nodes.front().second;
    nodes.pop();
    ++area;
    for (int i = 0; i < 4; ++i) {
      if ((wall[cx][cy] & (1 << i)) == 0) {
        int nx = cx + dx[i];
        int ny = cy + dy[i];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visit[nx][ny]) {
          visit[nx][ny] = true;
          nodes.push(make_pair(nx, ny));
        }
      }
    }
  }

  return area;
}

void Solve() {
  rooms = 0;
  max_area = 0;
  memset(visit, 0, sizeof(visit));

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (visit[i][j]) continue;
      ++rooms;
      int area = Bfs(i, j);
      if (area > max_area) max_area = area;
    }
  }
}

int main() {
  ReadData();
  Solve();
  cout << rooms << endl;
  cout << max_area << endl;

  return 0;
}
