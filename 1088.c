// 2010-03-04 18:34:35
#include <stdio.h>
#include <memory.h>

int r, c;
int h[100][100];
int f[100][100];

void ReadData()
{
  int i, j;

  scanf("%d %d", &r, &c);
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
      scanf("%d", &h[i][j]);
}

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

void dfs(int x, int y)
{
  int k, nx, ny;

  f[x][y] = 1;
  for (k = 0; k < 4; k++)
  {
    nx = x + dx[k];
    ny = y + dy[k];
    if (nx >= 0 && nx < r && ny >= 0 && ny < c && h[x][y] > h[nx][ny])
    {
      if (f[nx][ny] == 0)
        dfs(nx, ny);
      if (f[nx][ny] + 1 > f[x][y])
        f[x][y] = f[nx][ny] + 1;
    }
  }
}

void Process()
{
  int i, j, ans;

  memset(f, 0, sizeof(f));
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
      if (f[i][j] == 0)
        dfs(i, j);
  ans = 1;
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
      if (f[i][j] > ans)
        ans = f[i][j];
  printf("%d\n", ans);
}

int main()
{
  ReadData();
  Process();
  return 0;
}
