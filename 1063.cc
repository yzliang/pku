#include <cstdlib>
#include <iostream>
using namespace std;

int n;
int a[30];

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    if (n % 2 != 0)
      cout << "YES" << endl;
    else {
      int odd = 0, even = 0;
      for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
          if (i % 2 == 0)
            even++;
          else
            odd++;
        }
      }
      if (abs(odd - even) <= 1)
        cout << "YES" << endl;
      else
        cout << "NO" << endl;
    }
  }
  return 0;
}
