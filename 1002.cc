// 2009-12-15 18:37:30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

const char digit[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4',
            '5', '5', '5', '6', '6', '6', '7', 0, '7', '7',
            '8', '8', '8', '9', '9', '9', 0};

int n;
char numbers[100000][9];

void ReadData()
{
  int i, j, tot, len;
  char buff[100], ch;

  scanf("%d", &n);
  
  for (i = 0; i < n; i++)
  {
    scanf("%s", buff);
    tot = 0;
    len = strlen(buff);
    for (j = 0; j < len; j++)
      if (buff[j] >= 'A' && buff[j] <= 'Z')
      {
        ch = digit[buff[j] - 'A'];
        if (tot > 2)
          numbers[i][tot + 1] = ch;
        else
          numbers[i][tot] = ch;
        tot++;
      }
      else if (buff[j] >= '0' && buff[j] <= '9')
      {
        ch = buff[j];
        if (tot > 2)
          numbers[i][tot + 1] = ch;
        else
          numbers[i][tot] = ch;
        tot++;
      }
    numbers[i][3] = '-';
    numbers[i][8] = 0;
  }
}

int myCompare(const void *e1, const void *e2)
{
  char *p1 = (char *)e1;
  char *p2 = (char *)e2;
  return strcmp(p1, p2);
}

void Process()
{
  bool duplicate = false;
  int i, j, k;

  qsort(numbers, n, sizeof(char) * 9, myCompare);
  i = 0;
  while (i < n)
  {
    j = i + 1;
    while (j < n && strcmp(numbers[i], numbers[j]) == 0)
      j++;
    if (j - i > 1)
    {
      duplicate = true;
      printf("%s %d\n", numbers[i], j - i);
    }
    i = j;
  }
  if (!duplicate)
    printf("No duplicates.\n");
}

int main()
{
  char ch = '\n';
  ReadData();
  Process();
  return 0;
}
