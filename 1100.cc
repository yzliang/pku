#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int ans, n;
int op[12], num[12], bra[12];
int lb[12], rb[12];  // mark of brackets.
const char op_char[3] = {'+', '-', '*'};

void analyze(string& line) {
  memset(bra, 0, sizeof(bra));
  memset(lb, 0, sizeof(lb));
  memset(rb, 0, sizeof(rb));
  n = 0;
  stack<int> stack;
  int i = line.find('=') + 1;
  while (i < line.size()) {
    while (i < line.size() && isspace(line[i]))
      i++;
    if (i == line.size())
      break;
    if (line[i] == '(') {
      stack.push(n);
      lb[n]++;
      i++;
    } else if (line[i] == ')') {
      bra[stack.top()] = n - 1;
      rb[n - 1]++;
      stack.pop();
      i++;
    } else {
      num[n] = line[i] - '0';
      int j = i + 1;
      while (j < line.size() && isdigit(line[j]))
        num[n] = num[n] * 10 + line[j++] - '0';
      n++;
      i = j;
    }
  }
}

int eval(int l, int r) {
  if (l == r)
    return num[l];
  int ret = num[l], i = l + 1;
  while (i <= r) {
    int val, next;
    if (bra[i] == 0) {
      val = num[i];
      next = i + 1;
    } else {
      val = eval(i, bra[i]);
      next = bra[i] + 1;
    }
    if (op[i] == 0)
      ret += val;
    else if (op[i] == 1)
      ret -= val;
    else
      ret *= val;
    i = next;
  }
  return ret;
}

int main() {
  string line;
  int id = 1;
  while (cin >> ans) {
    if (ans == 0)
      break;
    getline(cin, line);
    analyze(line);
    bool found = false;
    for (int i = 0; i < pow(3, n - 1); i++) {
      int code = i;
      for (int j = n - 1; j > 0; j--) {
        op[j] = code % 3;
        code /= 3;
      }
      if (eval(0, n - 1) == ans) {
        found = true;
        break;
      }
    }
    cout << "Equation #" << id++ << ':' << endl;
    if (found) {
      cout << ans << '=';
      for (int i = 0; i < n; i++) {
        if (i > 0)
          cout << op_char[op[i]];
        for (int j = 0; j < lb[i]; j++)
          cout << '(';
        cout << num[i];
        for (int j = 0; j < rb[i]; j++)
          cout << ')';
      }
      cout << endl;
    } else
      cout << "Impossible" << endl;
    cout << endl;
  }
  return 0;
}
