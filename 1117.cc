#include <cmath>
#include <iostream>
#include <map>
using namespace std;

int n, len, r;
int num[11], factor[11], max_sum[11];
map<int, int> ans;

void search(int p, int sum) {
  if (p == 0) {
    // Disallow removing the leading zero.
    if (num[len] == 0 && r == len)
      return;
    int x = 0;
    for (int i = len; i >= 1; i--)
      x = x * 10 + num[i];
    if (ans.find(x) == ans.end())
      ans[x] = r;
    return;
  }
  int i = 0;
  while (sum + i * factor[p] + max_sum[p - 1] < n)
    i++;  // Not too small.
  while (i < 10 && sum + i * factor[p] <= n) {
    num[p] = i;
    search(p - 1, sum + i * factor[p]);
    i++;
  }
}

int main() {
  cin >> n;
  // Get length.
  for (int i = n; i > 0; i /= 10)
    len++;
  // Which digit to remove?
  for (r = 1; r <= len; r++) {
    for (int i = 1; i <= len; i++) {
      if (i < r)
        factor[i] = pow(10, i - 1) * 2;
      else if (i == r)
        factor[i] = pow(10, i - 1);
      else
        factor[i] = pow(10, i - 2) * 11;
    }
    for (int i = 1; i < len; i++)
      max_sum[i] = max_sum[i - 1] + 9 * factor[i];
    // Solve the equation.
    search(len, 0);
  }
  cout << ans.size() << endl;
  for (map<int, int>::iterator i = ans.begin(); i != ans.end(); i++) {
    char buffer[11];
    int len = 0, x = i->first;
    while (x > 0) {
      buffer[++len] = (char) (x % 10 + '0');
      x /= 10;
    }
    cout << i->first << " + ";
    for (int j = len; j >= 1; j--) {
      if (j != i->second)
        cout << buffer[j];
    }
    cout << " = " << n << endl;
  }
  return 0;
}
