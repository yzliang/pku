#include <iomanip>
#include <iostream>
using namespace std;

int n, k;
int len[10000];

bool check(int l) {
  if (l == 0) return true;
  int total = 0;
  for (int i = 0; i < n; i++)
    total += len[i] / l;
  return total >= k;
}

int main() {
  cin >> n >> k;
  float x;
  int l = 0, r = 0;
  for (int i = 0; i < n; i++) {
    cin >> x;
    len[i] = x * 100;
    if (len[i] > r) r = len[i];
  }
  while (l <= r) {
    int mid = l + (r - l) / 2;
    if (check(mid))
      l = mid + 1;
    else
      r = mid - 1;
  }
  cout << r / 100 << '.' << setfill('0') << setw(2) << r % 100 << endl;
  return 0;
}
