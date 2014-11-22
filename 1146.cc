#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  while (cin >> s) {
    if (s == "#") break;
    int i = s.size() - 1;
    while (i > 0 && s[i - 1] >= s[i])
      i--;
    if (i == 0)
      cout << "No Successor" << endl;
    else {
      int j = i;
      while (j + 1 < s.size() && s[j + 1] > s[i - 1])
        j++;
      char temp = s[i - 1];
      s[i - 1] = s[j];
      s[j] = temp;
      sort(s.begin() + i, s.end());
      cout << s << endl;
    }
  }
  return 0;
}
