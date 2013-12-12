#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const char* haab[19] = {"pop", "no", "zip", "zotz", "tzec", "xul",
  "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan",
  "pax", "koyab", "cumhu", "uayet"};

const char* tzolkin[20] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi",
  "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib",
  "caban", "eznab", "canac", "ahau"};

int main() {
  int t;
  cin >> t;
  cout << t << endl;
  for (; t > 0; t--) {
    int day, year;
    char month[10];
    scanf("%d. %s %d", &day, month, &year);
    int total = year * 365;
    for (int i = 0; i < 19; i++) {
      if (strcmp(month, haab[i]) == 0) {
        total += 20 * i + day;
        break;
      }
    }
    year = total / 260;
    total %= 260;
    day = total % 20;
    cout << (total % 13 + 1) << ' ' << tzolkin[day] << ' ' << year << endl;
  }
  return 0;
}
