// 2009-12-15 23:07:59
#include <stdio.h>

int main()
{
  int caseId = 1;
  int p, e, i, d;

  while (true)
  {
    scanf("%d %d %d %d", &p, &e, &i, &d);
    if (p < 0)
      break;
    while (p - 23 > d)
      p -= 23;
    while (p <= d)
      p += 23;
    while ((p - e) % 28 != 0 || (p - i) % 33 != 0)
      p += 23;
    printf("Case %d: the next triple peak occurs in %d days.\n", caseId, p - d);
    caseId++;
  }

  return 0;
}
