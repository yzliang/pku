// 2009-12-16 09:13:40
#include <stdio.h>

int n, m;

char dna[100][51];
int ord[100], inv[100];;

void ReadData()
{
  int i;

  scanf("%d %d", &n, &m);
  for (i = 0; i < m; i++)
    scanf("%s", dna[i]);
}

void Process()
{
  int i, j, k;
  int temp;

  for (i = 0; i < m; i++)
  {
    ord[i] = i;
    inv[i] = 0;
    for (j = 0; j < n; j++)
      for (k = j + 1; k < n; k++)
        if (dna[i][j] > dna[i][k])
          inv[i]++;
  }

  for (i = 0; i < m; i++)
    for (j = i + 1; j < m; j++)
      if ((inv[i] > inv[j]) || (inv[i] == inv[j] && ord[i] > ord[j]))
      {
        temp = inv[i];
        inv[i] = inv[j];
        inv[j] = temp;
        temp = ord[i];
        ord[i] = ord[j];
        ord[j] = temp;
      }

  for (i = 0; i < m; i++)
    printf("%s\n", dna[ord[i]]);
}

int main()
{
  ReadData();
  Process();

  return 0;
}
