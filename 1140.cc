#include <cstring>
#include <iostream>
using namespace std;

int a, b;
int f[1000];

int main() {
  while (cin >> a >> b) {
    if (a == 0 && b == 0)
      break;
    cout << '.';
    memset(f, 0, sizeof(f));
    int pos = 1, count = 1;
    while (a != 0 && f[a] == 0) {
      f[a] = pos++;
      a *= 10;
      cout << a / b;
      if (++count == 50) {
        cout << endl;
        count = 0;
      }
      a %= b;
    }
    if (count != 0)
      cout << endl;
    if (a == 0)
      cout << "This expansion terminates." << endl;
    else
      cout << "The last " << pos - f[a] << " digits repeat forever." << endl;
  }
  return 0;
}
