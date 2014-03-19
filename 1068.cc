// 2008-12-06 20:18:33
#include <iostream>
using namespace std;

int t, n;
int p[20], w[20];
char s[41];

void ReadData()
{
  int i;

  cin >> n;
  for (i = 0; i < n; i++)
    cin >> p[i];
}

void Process()
{
  int i, j, tot;
  bool matched[41];

  tot = j = 0;
  for (i = 0; i < n; i++)
  {
    while (tot < p[i])
    {
      s[j++] = '(';
      tot++;
    }
    s[j++] = ')';
  }
  memset(matched, 0, sizeof(matched));
  tot = 0;
  for (i = 0; i < n + n; i++)
    if (s[i] == ')')
    {
      j = i - 1;
      while (matched[j] || s[j] == ')')
        j--;
      matched[j] = true;
      w[tot] = 0;
      while (j <= i)
      {
        if (s[j] == ')')
          w[tot]++;
        j++;
      }
      tot++;
    }
  cout << w[0];
  for (i = 1; i < n; i++)
    cout << ' ' << w[i];
  cout << endl;
}

int main()
{
  cin >> t;
  for (; t > 0; t--)
  {
    ReadData();
    Process();
  }
  return 0;
}
