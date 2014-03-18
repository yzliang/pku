#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

struct ACM {
  int x, y, z;
  ACM(int x, int y, int z) : x(x), y(y), z(z) {}
};

int n, m, k, l;
bool map[62][62][62];  // [1,k] * [1,m] * [1,n]
bool visit[62][62][62];

const int dx[] = {0, 0, 0, 0, -1, 1};
const int dy[] = {0, 0, -1, 1, 0, 0};
const int dz[] = {-1, 1, 0, 0, 0, 0};

int main() {
  while (cin >> n >> m >> k >> l) {
    if (n == 0 && m == 0 && k == 0 && l == 0)
      break;
    memset(map, 0, sizeof(map));
    for (int i = 0; i < l; i++) {
      int pos;
      cin >> pos;
      int d1 = pos / (n * m);
      pos %= n * m;
      int d2 = pos / n;
      pos %= n;
      map[d1 + 1][d2 + 1][pos + 1] = true;
    }
    // BFS from (0,0,0).
    int ans = 0;
    queue<ACM> q;
    q.push(ACM(0, 0, 0));
    memset(visit, 0, sizeof(visit));
    visit[0][0][0] = true;
    while (!q.empty()) {
      ACM head = q.front();
      q.pop();
      for (int i = 0; i < 6; i++) {
        int nx = head.x + dx[i], ny = head.y + dy[i], nz = head.z + dz[i];
        if (nx < 0 || nx > k + 1 || ny < 0 || ny > m + 1 || nz < 0 ||
            nz > n + 1)
          continue;
        if (visit[nx][ny][nz]) continue;
        if (!map[nx][ny][nz]) {
          visit[nx][ny][nz] = true;
          q.push(ACM(nx, ny, nz));
        } else
          ans++;
      }
    }
    cout << "The number of faces needing shielding is " << ans << '.' <<  endl;
  }
  return 0;
}
