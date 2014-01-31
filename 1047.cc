#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int n;
string s;
int num[100];
int profile[10];

bool judge() {
  int times[100];
  for (int i = 2; i <= n; i++) {
    memcpy(times, num, sizeof(times));
    for (int j = 0; j < n; j++)
      times[j] *= i;
    for (int j = 0; j < n; j++) {
      if (times[j] >= 10) {
        times[j + 1] += times[j] / 10;
        times[j] %= 10;
      }
    }
    if (times[n] > 0) return false;
    int profile1[10] = {0};
    for (int j = 0; j < n; j++)
      profile1[times[j]]++;
    for (int j = 0; j < 10; j++)
      if (profile1[j] != profile[j]) return false;
  }
  return true;
}

int main() {
  while (cin >> s) {
    n = s.length();
    memset(num, 0, sizeof(num));
    memset(profile, 0, sizeof(profile));
    for (int i = 0; i < n; i++) {
      num[i] = s[n - i - 1] - '0';
      profile[num[i]]++;
    }
    cout << s << " is " << (judge() ? "cyclic" : "not cyclic") << endl;
  }
  return 0;
}
