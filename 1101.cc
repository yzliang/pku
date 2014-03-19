#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct State {
  int x, y, d, segs;
  State(int x, int y, int d, int segs) : x(x), y(y), d(d), segs(segs) {}
};

const int dx[] = {1, 0, 0, -1};
const int dy[] = {0, 1, -1, 0};

int w, h, x1, y1, x2, y2;
// index1:row, index2:column
bool map[77][77]; 
int segs[77][77][4];

int compute() {
  memset(segs, 0, sizeof(segs));
  queue<State> q;
  for (int i = 0; i < 4; i++) {
    int nx = x1 + dx[i], ny = y1 + dy[i];
    if (nx == x2 && ny == y2)
      return 1;
    if (map[ny][nx])
      continue;
    segs[ny][nx][i] = 1;
    q.push(State(nx, ny, i, 1));
  }
  while (!q.empty()) {
    State head = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      if (i + head.d == 3)
        continue;  // Can't turn over by 180 degree.
      int nx = head.x + dx[i], ny = head.y + dy[i];
      if (nx < 0 || nx > w + 1 || ny < 0 || ny > h + 1)
        continue;
      int nsegs = head.segs + (i != head.d);
      if (segs[ny][nx][i] == 0 || nsegs < segs[ny][nx][i]) {
        segs[ny][nx][i] = nsegs;
        if (!map[ny][nx])
          q.push(State(nx, ny, i, nsegs));
      }
    }
  }
  int ans = -1;
  for (int i = 0; i < 4; i++)
    if (segs[y2][x2][i] > 0 && (ans == -1 || segs[y2][x2][i] < ans))
      ans = segs[y2][x2][i];
  return ans;
}

int main() {
  string line;
  int board_id = 1;
  while (cin >> w >> h) {
    if (w == 0 && h == 0)
      break;
    getline(cin, line);
    memset(map, 0, sizeof(map));
    for (int i = 1; i <= h; i++) {
      getline(cin, line);
      for (int j = 0; j < w; j++)
        map[i][j + 1] = line[j] == 'X';
    }
    cout << "Board #" << board_id++ << ':' << endl;
    int pair_id = 1;
    while (cin >> x1 >> y1 >> x2 >> y2) {
      if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
        break;
      cout << "Pair " << pair_id++ << ": ";
      int ret = compute();
      if (ret == -1)
        cout << "impossible." << endl;
      else
        cout << ret << " segments." << endl;
    }
    cout << endl;
  }
  return 0;
}
