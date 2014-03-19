// 2009-03-05 20:34:50
#include <iostream>
#include <cmath>
using namespace std;

const int UPPER = 31275;
unsigned int sum[UPPER];
int p10[10];

void PreCalc()
{
  int i, j, len, bit;

  p10[0] = 1;
  for (i = 1; i < 10; i++)
    p10[i] = p10[i - 1] * 10;
  sum[0] = 0;
  for (i = 1; i < UPPER; i++)
  {
    bit = floor(log10((double)i)) + 1;
    len = 0;
    for (j = 1; j < bit; j++)
      len += j * 9 * p10[j - 1];
    len += bit * (i - p10[bit - 1] + 1);
    sum[i] = sum[i - 1] + len;
  }
}

int main()
{
  int t, i, j, bit, len;
  unsigned int n;

  PreCalc();
  cin >> t;
  for (; t > 0; t--)
  {
    cin >> n;
    i = 1;
    while (n > sum[i])
      i++;
    n -= sum[i - 1];
    bit = floor(log10((double)i)) + 1;
    len = 9;
    j = 1;
    while (len < n)
    {
      n -= len;
      j++;
      len = j * 9 * p10[j - 1];
    }
    i = p10[j - 1] + (n - 1) / j;
    n = (n - 1) % j + 1;
    n = j - n + 1;
    cout << i / p10[n - 1] % 10 << endl;
  }
  return 0;
}
