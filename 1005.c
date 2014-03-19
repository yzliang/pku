// 2009-12-15 22:54:16
#include <stdio.h>

const double pi = 3.1415926;

int main()
{
  int n, i, z;
  double x, y, r2, area;

  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%lf %lf", &x, &y);
    r2 = x * x + y * y;
    area = 0;
    z = 0;
    do
    {
      z++;
      area += 50;
    } while (area * 2 < r2 * pi);
    printf("Property %d: This property will begin eroding in year %d.\n", i + 1, z);
  }
  printf("END OF OUTPUT.\n");

  return 0;
}
