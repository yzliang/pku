// 2009-12-15 17:36:56
#include <stdio.h>

int main()
{
  double sum, money;
  int i;

  sum = 0;
  for (i = 0; i < 12; i++)
  {
    scanf("%lf", &money);
    sum += money;
  }
  printf("$%.2lf\n", sum / 12);

  return 0;
}
