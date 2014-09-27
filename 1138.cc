#include <cstring>
#include <iostream>
using namespace std;

int n, m;
char a[20][20], b[20][20];

/*
 * All patterns (rotated, not mirrored): 
 *   xx xx   x  xx x  x    xx xxx  x   x x  xxx xx  x  x  xxx  x xxxx x
 *   xx  xx xx xx  xx xxx  x    x  x xxx x  x    x xxx xx  x  xx      x
 *          x       x      x      xx     xx      x     x       x      x
 *                                                                    x
 */
const int id[19] = {0, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6};
const int dx[19][3] = {
  {0, 1, 1}, {0, 1, 1}, {1, 1, 2}, {0, 1, 1}, {1, 1, 2}, {1, 1, 1},
  {0, 1, 2}, {0, 0, 1}, {1, 2, 2}, {1, 1, 1}, {1, 2, 2}, {0, 0, 1},
  {0, 1, 2}, {1, 1, 1}, {1, 1, 2}, {0, 0, 1}, {1, 1, 2}, {0, 0, 0},
  {1, 2, 3}
};
const int dy[19][3] = {
  {1, 0, 1}, {1, 1, 2}, {-1, 0, -1}, {1, -1, 0}, {0, 1, 1}, {0, 1, 2},
  {1, 0, 0}, {1, 2, 2}, {0, -1, 0}, {-2, -1, 0}, {0, 0, 1}, {1, 2, 0},
  {1, 1, 1}, {-1, 0, 1}, {0, 1, 0}, {1, 2, 1}, {-1, 0, 0}, {1, 2, 3},
  {0, 0, 0}
};

bool yes;
int num_used;  // #used patterns
int num_free;  // #free cells (not including 'o')
bool used[7];

const int MAX_GAMES = 10;
int num_games;  // num. of different games w.r.t all remaining 'x' squares.
char games[MAX_GAMES][20][20];

bool is_unique() {
  if (num_games <= 2) return true;
  int board[20][20] = {0};
  for (int i = 0; i < num_games; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < m; k++) {
        if (games[i][j][k] != 'o')
          board[j][k]++;
      }
    }
  }
  bool excluded[MAX_GAMES] = {0};
  for (int rest = num_games; rest > 1; rest--) {
    int x = -1, y = -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == rest - 1) {
          x = i;
          y = j;
          break;
        }
      }
      if (x != -1) break;
    }
    if (x == -1) return false;
    int who = -1;
    for (int i = 0; i < num_games; i++) {
      if (!excluded[i] && games[i][x][y] == 'o') {
        who = i;
        break;
      }
    }
    excluded[who] = true;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (games[who][i][j] != 'o')
          board[i][j]--;
      }
    }
  }
  return true;
}

void search(int x, int y) {
  if (x == n) {
    // A game must have all seven patterns.
    bool all_used = true;
    for (int i = 0; i < 7; i++) {
      if (!used[i]) {
        all_used = false;
        break;
      }
    }
    if (!all_used) return;
    // Deduplicate.
    bool old = false;
    for (int i = 0; i < num_games; i++) {
      bool same = true;
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < m; k++) {
          if ((games[i][j][k] == 'o') ^ (b[j][k] == 'o')) {
            same = false;
            break;
          }
        }
        if (!same) break;
      }
      if (same) {
        old = true;
        break;
      }
    }
    if (old) return;
    // Add game.
    memcpy(games[num_games++], b, sizeof(b));
    // Unique?
    if (!is_unique())
      yes = false;
    return;
  }
  int ny = y == m - 1 ? 0 : y + 1;
  int nx = ny == 0 ? x + 1 : x;
  if (b[x][y] != '.') {
    search(nx, ny);
    return;
  }
  // (x, y) is the upper-left of a pattern.
  for (int i = 0; i < 19; i++) {
    if (used[id[i]]) continue;
    bool ok = true;
    for (int j = 0; j < 3; j++) {
      int xx = x + dx[i][j];
      int yy = y + dy[i][j];
      if (xx < 0 || xx == n || yy < 0 || yy == m || b[xx][yy] != '.') {
        ok = false;
        break;
      }
    }
    if (!ok) continue;
    used[id[i]] = true;
    num_used++;
    num_free -= 4;
    b[x][y] = id[i] + '1';
    for (int j = 0; j < 3; j++)
      b[x + dx[i][j]][y + dy[i][j]] = id[i] + '1';
    search(nx, ny);
    // Backtrack.
    used[id[i]] = false;
    num_used--;
    num_free += 4;
    for (int j = 0; j < 3; j++)
      b[x + dx[i][j]][y + dy[i][j]] = '.';
    b[x][y] = '.';
    // Prune.
    if (!yes) return;
  }
  // (x, y) is not covered.
  if (a[x][y] != 'x') {
    b[x][y] = 'o';
    num_free--;
    if (num_free >= (7 - num_used) * 4)  // Prune.
      search(nx, ny);
    num_free++;
    b[x][y] = '.';
  }
}

int main() {
  int game_id = 1;
  while (cin >> n >> m) {
    if (n == 0 && m == 0)
      break;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    num_free = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (a[i][j] == 'o')
          b[i][j] = 'o';
        else {
          b[i][j] = '.';
          num_free++;
        }
      }
    }
    memset(used, 0, sizeof(used));
    num_used = 0;
    num_games = 0;
    yes = true;
    search(0, 0);
    cout << "Game #" << game_id++ << endl;
    cout << (yes ? "yes." : "no.") << endl << endl;
  }
  return 0;
}
