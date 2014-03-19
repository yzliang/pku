// 2009-12-15 17:43:31
#include <stdio.h>

int main()
{
  double maxLength, currentLength;
  int ans;

  while (true)
  {
    scanf("%lf", &maxLength);
    if (maxLength == 0.0)
      break;
    ans = 0;
    currentLength = 0.0;
    do
    {
      ans++;
      currentLength += 1 / (double)(ans + 1);
    } while (currentLength < maxLength);
    printf("%d card(s)\n", ans);
  }

  return 0;
}
