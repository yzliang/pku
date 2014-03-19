// 2008-11-15 15:13:36
#include <iostream>
using namespace std;

struct move
{
  int left, right;
  bool done;
};

int comparemove(const void *elem1, const void *elem2)
{
  move *p1 = (move *)elem1;
  move *p2 = (move *)elem2;
  if (p1->left == p2->left)
    return p1->right - p2->right;
  else
    return p1->left - p2->left;
}

int main()
{
  int t, n, i, j, k, time;
  move m[200];

  cin >> t;
  for (; t > 0; t--)
  {
    /////////////////////////////////////////
    //read data
    cin >> n;
    for (i = 0; i < n; i++)
    {
      cin >> m[i].left >> m[i].right;
      if (m[i].left % 2)
        m[i].left++;
      if (m[i].right % 2)
        m[i].right++;
      if (m[i].left > m[i].right)
      {
        j = m[i].left;
        m[i].left = m[i].right;
        m[i].right = j;
      }
      m[i].done = false;
    }
    qsort(m, n, sizeof(move), comparemove);
    /////////////////////////////////////////
    //calculate the answer
    time = 0;
    for (i = 0; i < n; i++)
      if (!m[i].done)
      {
        m[i].done = true;
        j = i + 1;
        k = m[i].right;
        while (j < n)
        {
          if (!m[j].done && m[j].left > k)
          {
            m[j].done = true;
            k = m[j].right;
          }
          j++;
        }
        time += 10;
      }
    cout << time << endl;
  }
  return 0;
}
