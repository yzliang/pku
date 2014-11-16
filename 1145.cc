#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int target;
bool ans;

char next_ch() {
  char ch;
  while (cin >> ch && isspace(ch));
  return ch;
}

bool parse(bool eat_left, int sum) {
  if (eat_left)
    next_ch();  // eat '('.
  char c = next_ch();
  if (c == ')')
    return true;  // is null.
  else {
    bool negative = c == '-';
    int num = (c == '-') ? 0 : (c - '0');
    while (cin >> c && isdigit(c))
      num = num * 10 + (c - '0');
    if (negative)
      num = -num;
    bool l_null = c == '(' ? parse(false, sum + num) : parse(true, sum + num);
    bool r_null = parse(true, sum + num);
    next_ch();  // eat ')'.
    if (l_null && r_null && sum + num == target)
      ans = true;
    return false;
  }
}

int main() {
  while (cin >> target) {
    ans = false;
    parse(true, 0);
    cout << (ans ? "yes" : "no") << endl;
  }
  return 0;
}
