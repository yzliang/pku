// 2009-03-03 22:18:53
#include <iostream>
using namespace std;

int l1, l2;
int s1[110], s2[110];

int Translate(char ch)
{
  switch (ch)
  {
  case 'A':
    return 0;
  case 'C':
    return 1;
  case 'G':
    return 2;
  case 'T':
    return 3;
  }
}

void ReadData()
{
  int i;
  char str[110];

  cin >> l1 >> str;
  for (i = 0; i < l1; i++)
    s1[i + 1] = Translate(str[i]);
  cin >> l2 >> str;
  for (i = 0; i < l2; i++)
    s2[i + 1] = Translate(str[i]);
}

const int mark[5][5] = {
  5, -1, -2, -1, -3,
  -1, 5, -3, -2, -4,
  -2, -3, 5, -2, -2,
  -1, -2, -2, 5, -1,
  -3, -4, -2, -1, 0};

void Process()
{
  int i, j;
  int f[110][110];

  f[0][0] = 0;
  for (i = 1; i <= l1; i++)
    f[i][0] = f[i - 1][0] + mark[s1[i]][4];
  for (i = 1; i <= l2; i++)
    f[0][i] = f[0][i - 1] + mark[s2[i]][4];
  for (i = 1; i <= l1; i++)
    for (j = 1; j <= l2; j++)
    {
      if (f[i - 1][j - 1] + mark[s1[i]][s2[j]] > f[i - 1][j] + mark[s1[i]][4])
        f[i][j] = f[i - 1][j - 1] + mark[s1[i]][s2[j]];
      else
        f[i][j] = f[i - 1][j] + mark[s1[i]][4];
      if (f[i][j - 1] + mark[s2[j]][4] > f[i][j])
        f[i][j] = f[i][j - 1] + mark[s2[j]][4];
    }
  cout << f[l1][l2] << endl;
}

int main()
{
  int t;

  cin >> t;
  for (; t > 0; t--)
  {
    ReadData();
    Process();
  }
  return 0;
}
