#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
int code[20000];
int sign_x[10000];
int sign_y[10000];

const int dx[5] = {0, 1, -1, -1, 1};
const int dy[5] = {0, 1, 1, -1, -1};

vector<int> solve(int sign[], int start) {
  vector<int> ans;
  int l = start;
  int r = start + n - 1;
  // Check sign[n - 1], sign[n - 2], ..., sign[1].
  for (int i = n - 1; i > 0; i--) {
    if (sign[i] != sign[i - 1]) {
      ans.push_back(sign[i] * code[r]);
      r--;
    } else {
      int head_sign = i % 2 == 0 ? sign[i] : -sign[i];
      ans.push_back(head_sign * code[l]);
      l++;
    }
  }
  // Solve the initial case: one sign and one number.
  ans.push_back(sign[0] * code[l]);
  return ans;
}

int main() {
  cin >> n;
  for (int i = 0; i < n + n; i++)
    cin >> code[i];
  for (int i = 0; i < n; i++) {
    int region;
    cin >> region;
    sign_x[i] = dx[region];
    sign_y[i] = dy[region];
  }

  sort(code, code + n + n);
  vector<int> x_ans = solve(sign_x, 0);
  vector<int> y_ans = solve(sign_y, n);
  for (int i = n - 1; i >= 0; i--) {
    if (x_ans[i] > 0)
      cout << '+';
    cout << x_ans[i];
    cout << ' ';
    if (y_ans[i] > 0)
      cout << '+';
    cout << y_ans[i];
    cout << endl;
  }

  return 0;
}
