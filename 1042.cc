#include <cstring>
#include <iostream>
using namespace std;

int n, h;
int f[25], d[25], t[25];
int best;
int ans[25];

void fishing(int end) {
  int time = h * 12;
  for (int i = 0; i < end; i++)
    time -= t[i];
  if (time <= 0) return;
  int num = 0;
  int rest[25], stay[25] = {0};
  memcpy(rest, f, sizeof(rest));
  for (; time > 0; time--) {
    int j = 0, max_num = rest[0];
    for (int i = 1; i <= end; i++) {
      if (rest[i] > max_num) {
        j = i;
        max_num = rest[i];
      }
    }
    num += max_num;
    stay[j]++;
    if (rest[j] >= d[j])
      rest[j] -= d[j];
    else
      rest[j] = 0;
  }
  if (num > best) {
    best = num;
    memcpy(ans, stay, sizeof(ans));
  }
}

int main() {
  bool first = true;
  while (cin >> n) {
    if (n == 0) break;
    cin >> h;
    for (int i = 0; i < n; i++)
      cin >> f[i];
    for (int i = 0; i < n; i++)
      cin >> d[i];
    for (int i = 0; i < n - 1; i++)
      cin >> t[i];
    best = -1;
    for (int i = 0; i < n; i++)
      fishing(i);
    if (first)
      first = false;
    else
      cout << endl;
    for (int i = 0; i < n - 1; i++)
      cout << ans[i] * 5 << ", ";
    cout << ans[n - 1] * 5 << endl;
    cout << "Number of fish expected: " << best << endl;
  }
  return 0;
}
