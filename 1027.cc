#include <cstdio>
#include <cstring>

struct Position {
  int r, c;
};

char map[10][16];
char buffer[100];
Position best[200], cluster[200];
int best_len, len;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int main() {
  int t;
  scanf("%d", &t);
  for (int id = 1; id <= t; id++) {
    for (int i = 0; i < 10; i++)
      scanf("%s", map[i]);
    if (id > 1) putchar('\n');
    printf("Game %d:\n\n", id);
    int score = 0, step = 0;
    while (true) {
      best_len = 0;
      bool go[10][15] = {0};
      for (int c = 0; c < 15; c++) {
        for (int r = 9; r >= 0; r--) {
          if (go[r][c] || map[r][c] == ' ') continue;
          len = 1;
          cluster[0].r = r;
          cluster[0].c = c;
          go[r][c] = true;
          int head = 0;
          while (head < len) {
            for (int i = 0; i < 4; i++) {
              int nr = cluster[head].r + dx[i];
              int nc = cluster[head].c + dy[i];
              if (nr < 0 || nr >= 10 || nc < 0 || nc >= 15) continue;
              if (go[nr][nc] || map[nr][nc] != map[r][c]) continue;
              go[nr][nc] = true;
              cluster[len].r = nr;
              cluster[len].c = nc;
              len++;
            }
            head++;
          }
          if (len > best_len) {
            best_len = len;
            memcpy(best, cluster, sizeof(Position) * best_len);
          }
        }
      }
      if (best_len <= 1) {
        if (best_len == 0) score += 1000;
        break;
      }
      int delta = (best_len - 2) * (best_len - 2);
      score += delta;
      printf("Move %d at (%d,%d): removed %d balls of color %c,", ++step,
             10 - best[0].r, best[0].c + 1, best_len,
             map[best[0].r][best[0].c]);
      printf(" got %d points.\n", delta);
      // Remove.
      for (int i = 0; i < best_len; i++)
        map[best[i].r][best[i].c] = ' ';
      // Compress.
      for (int c = 0; c < 15; c++) {
        int next = 9;
        for (int r = 9; r >= 0; r--) {
          if (map[r][c] != ' ')
            map[next--][c] = map[r][c];
        }
        for (int r = 0; r <= next; r++)
          map[r][c] = ' ';
      }
      int next = 0;
      for (int c = 0; c < 15; c++) {
        bool empty = true;
        for (int r = 0; r < 10; r++) {
          if (map[r][c] != ' ') {
            empty = false;
            break;
          }
        }
        if (empty) continue;
        if (next != c) {
          for (int r = 0; r < 10; r++)
            map[r][next] = map[r][c];
        }
        next++;
      }
      for (int c = next; c < 15; c++)
        for (int r = 0; r < 10; r++)
          map[r][c] = ' ';
    }
    int rest = 0;
    for (int r = 0; r < 10; r++)
      for (int c = 0; c < 15; c++)
        rest += map[r][c] != ' ';
    printf("Final score: %d, with %d balls remaining.\n", score, rest);
  }
  return 0;
}
