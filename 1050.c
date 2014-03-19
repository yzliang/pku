// 2010-03-07 17:05:32
#include <stdio.h>
#include <memory.h>

int n;
int a[100][100];
int f[100];

void ReadData()
{
  int i, j;

  scanf("%d", &n);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%d", &a[i][j]);
}

void Process()
{
  int i, j, k;
  int value;
  int ans;

  ans = -200;
  for (i = 0; i < n; i++)
  {
    memset(f, 0, sizeof(f));
    for (j = i; j < n; j++)
    {
      for (k = 0; k < n; k++)
        f[k] += a[j][k];
      value = 0;
      for (k = 0; k < n; k++) 
      {
        value += f[k];
        if (value > ans)
          ans = value;
        if (value < 0)
          value = 0;
      }
    }
  }
  
  printf("%d\n", ans);
}

int main()
{
  ReadData();
  Process();

  return 0;
}
