#include <iostream>
#include <vector>
using namespace std;

int Get2(int x) {
  if (x <= 1)
    return 0;
  else
    return x / 2 + Get2(x / 2);
}

int Get5(int x) {
  if (x <= 4)
    return 0;
  else
    return x / 5 + Get5(x / 5);
}

int GetLastOdd(int x, int last) {
  if (x == 0)
    return 0;
  int ans = x / 10 + (x % 10 >= last);
  return ans + GetLastOdd(x / 5, last);
}

int GetLast(int x, int last) {
  if (x == 0)
    return 0;
  int ans = x / 10 + (x % 10 >= last);
  return ans + GetLast(x / 2, last) + GetLastOdd(x / 5, last);
}

// Let fac = n * (n - 1) * ... * (n - m + 1).
// Returns the last non-zero digit of fac.
int Solve(int n, int m) {
  // Get the total number of factor 2 in fac.
  int num2 = Get2(n) - Get2(n - m);
  // Get the total number of factor 5 in fac.
  int num5 = Get5(n) - Get5(n - m);

  // Get the amount of the numbers in [n - m + 1, ..., n] which end with digit
  // 3 after removing all factors 2 and 5.
  int d3 = GetLast(n, 3) - GetLast(n - m, 3);
  // Get the amount of the numbers in [n - m + 1, ..., n] which end with digit
  // 7 after removing all factors 2 and 5.
  int d7 = GetLast(n, 7) - GetLast(n - m, 7);
  // Get the amount of the numbers in [n - m + 1, ..., n] which end with digit
  // 9 after removing all factors 2 and 5.
  int d9 = GetLast(n, 9) - GetLast(n - m, 9);

  static int last2[4] = {6, 2, 4, 8};
  static int last3[4] = {1, 3, 9, 7};
  static int last7[4] = {1, 7, 9, 3};
  static int last9[2] = {1, 9};
  int last = (d3 > 0 ? last3[d3 % 4] : 1) * (d7 > 0 ? last7[d7 % 4] : 1) *
    (d9 > 0 ? last9[d9 % 2] : 1) % 10;
  if (num2 > num5) {
    return last * last2[(num2 - num5) % 4] % 10;
  } else if (num2 < num5) {
    return 5;
  } else {
    return last;
  }
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    cout << Solve(n, m) << endl;
  }
  return 0;
}
