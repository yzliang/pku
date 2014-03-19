// 2009-01-21 21:31:52
#include <stdio.h>
#include <string.h>

char dict[10001][16];
int tot;

void ReadDict()
{
  tot = 0;
  while (1)
  {
    gets(dict[tot]);
    if (dict[tot][0] == '#')
      break;
    tot++;
  }
}

bool substring(char *a, char *b)
{
  int i = 0, j = 0;
  while (i < strlen(a) && j < strlen(b))
    if (a[i] == b[j])
    {
      i++;
      j++;
    }
    else
      j++;
  return i == strlen(a);
}

void Process()
{
  char word[16];
  int ans[10000];
  int i, j, diff, wordlen, totans;
  bool correct;

  while (1)
  {
    gets(word);
    wordlen = strlen(word);
    if (word[0] == '#')
      break;
    correct = false;
    totans = 0;
    for (i = 0; i < tot; i++)
      if (strlen(dict[i]) == wordlen)
      {
        diff = 0;
        for (j = 0; j < wordlen; j++)
          if (word[j] != dict[i][j])
            diff++;
        if (diff == 0)
        {
          correct = true;
          break;
        }
        else if (diff == 1)
          ans[totans++] = i;
      }
      else if (strlen(dict[i]) + 1 == wordlen && substring(dict[i], word))
        ans[totans++] = i;
      else if (strlen(dict[i]) - 1 == wordlen && substring(word, dict[i]))
        ans[totans++] = i;
    if (correct)
      printf("%s is correct\n", word);
    else
    {
      printf("%s:", word);
      for (i = 0; i < totans; i++)
        printf(" %s", dict[ans[i]]);
      printf("\n");
    }
  }
}

int main()
{
  ReadDict();
  Process();
  return 0;
}
