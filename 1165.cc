#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int sum, d;
bool prime[100000];
int num[25];
int sum_row[5], sum_col[5];
int sum_diag1, sum_diag2;  // For the two diagonals (diag1: up-to-down).
vector< vector<int> > solutions;

// For search order.
struct Position {
  int r, c;
} positions[25];
const int next_p[25] = {
  -1, 11, 3, 13, 24,
  7, 18, 17, 9, 14,
  5, 2, 4, 10, 19,
  -1, 8, 15, 16, 21,
  6, 22, 23, 1, 20
};

void CalculatePrimes() {
  fill(prime, prime + 100000, true);
  for (int i = 2; i < 100000; i++) {
    if (prime[i]) {
      for (int j = i + i; j < 100000; j += i)
        prime[j] = false;
    }
  }
}

bool IsPrime(int r, int c, int dr, int dc) {
  int x = num[r * 5 + c];
  if (x == 0) return false;  // Disallow leading zeros.
  for (int i = 1; i < 5; i++) {
    r += dr;
    c += dc;
    x = x * 10 + num[r * 5 + c];
  }
  return prime[x];
}

void Search(int pos) {
  int r = positions[pos].r, c= positions[pos].c;
  // Judge the final states.
  switch (pos) {
    case 18:
      num[pos] = sum - sum_diag1;
      if (num[pos] > 9) return;
      if (sum_row[r] + num[pos] > sum) return;
      if (sum_col[c] + num[pos] > sum) return;
      sum_row[r] += num[pos];
      sum_col[c] += num[pos];
      if (IsPrime(0, 0, 1, 1)) Search(next_p[pos]);
      sum_row[r] -= num[pos];
      sum_col[c] -= num[pos];
      return;
    case 8:
      num[pos] = sum - sum_diag2;
      if (num[pos] > 9) return;
      if (sum_row[r] + num[pos] > sum) return;
      if (sum_col[c] + num[pos] > sum) return;
      sum_row[r] += num[pos];
      sum_col[c] += num[pos];
      if (IsPrime(4, 0, -1, 1)) Search(next_p[pos]);
      sum_row[r] -= num[pos];
      sum_col[c] -= num[pos];
      return;
    case 11:
    case 13:
    case 17:
    case 19:
      num[pos] = sum - sum_col[c];
      if (num[pos] > 9) return;
      if (sum_row[r] + num[pos] > sum) return;
      sum_row[r] += num[pos];
      if (IsPrime(0, c, 1, 0)) Search(next_p[pos]);
      sum_row[r] -= num[pos];
      return;
    case 3:
    case 7:
    case 10:
    case 23:
      num[pos] = sum - sum_row[r];
      if (num[pos] > 9) return;
      if (sum_col[c] + num[pos] > sum) return;
      sum_col[c] += num[pos];
      if (IsPrime(r, 0, 0, 1)) Search(next_p[pos]);
      sum_col[c] -= num[pos];
      return;
    case 15:
      if (sum_col[c] != sum_row[r]) return;
      num[pos] = sum - sum_row[r];
      if (num[pos] > 9) return;
      if (IsPrime(r, 0, 0, 1) && IsPrime(0, c, 1, 0)) {
        solutions.push_back(vector<int>());
        vector<int> &v = solutions.back();
        for (int i = 0; i < 25; i++)
          v.push_back(num[i]);
      }
      return;
  }
  // Fill the intermediate states.
  for (int i = 0; i < 10; i++) {
    // Heads can't be 0.
    if (i == 0 && (pos < 5 || pos % 5 == 0)) continue;
    // Tails can't be multiples of 2 or 5.
    if ((pos % 5 == 4 || pos >= 20) && (i % 2 == 0 || i % 5 == 0)) continue;
    // Check for sums.
    if (sum_row[r] + i > sum || sum_col[c] + i > sum) break;
    if (r == c && sum_diag1 + i > sum) break;
    if (r + c == 4 && sum_diag2 + i > sum) break;
    // Search next.
    num[pos] = i;
    sum_row[r] += i;
    sum_col[c] += i;
    if (r == c) sum_diag1 += i;
    if (r + c == 4) sum_diag2 += i;
    Search(next_p[pos]);
    sum_row[r] -= i;
    sum_col[c] -= i;
    if (r == c) sum_diag1 -= i;
    if (r + c == 4) sum_diag2 -= i;
  }
}

int main() {
  CalculatePrimes();

  cin >> sum >> d;

  // All positions.
  for (int i = 0; i < 25; i++) {
    positions[i].r = i / 5;
    positions[i].c = i % 5;
  }

  // Search.
  num[0] = d;
  sum_row[0] = d;
  sum_col[0] = d;
  sum_diag1 = d;
  Search(12);

  sort(solutions.begin(), solutions.end());
  for (int i = 0; i < solutions.size(); i++) {
    if (i > 0) cout << endl;
    for (int j = 0; j < 25; j++) {
      cout << solutions[i][j];
      if (j % 5 == 4) cout << endl;
    }
  }
  return 0;
}
