#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int n, m;
bool low_true, high_true;
bool used[101];
int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
  59, 61, 67, 71, 73, 79, 83, 89, 97};
int ip[101];

void search_high(int p) {
  if (p == 1) {
    high_true = true;
    return;
  }
  // Find p's largest prime factor.
  int j = ip[min(100, p)];
  while (j >= 0 && (primes[j] > p || p % primes[j] != 0))
    j--;
  if (j < 0) return;
  // Enumerate a grape.
  for (int i = 1; i <= min(100, p) / primes[j]; i++) {
    int factor = primes[j] * i;
    if (p % factor != 0 || used[factor]) continue;
    used[factor] = true;
    search_high(p / factor);
    if (high_true)  // Terminate condition.
      return;
    used[factor] = false;
  }
}

void search_low(int p) {
  if (p == 1) {
    low_true = true;
    search_high(n);
    return;
  }
  // Find p's largest prime factor.
  int j = ip[min(100, p)];
  while (j >= 0 && (primes[j] > p || p % primes[j] != 0))
    j--;
  if (j < 0) return;
  // Enumerate a grape.
  for (int i = 1; i <= min(100, p) / primes[j]; i++) {
    int factor = primes[j] * i;
    if (p % factor != 0 || used[factor]) continue;
    used[factor] = true;
    search_low(p / factor);
    if (low_true && high_true)  // Terminate condition.
      return;
    used[factor] = false;
  }
}

int main() {
  // Preprocess.
  int j = 24;
  for (int i = 100; i >= 2; i--) {
    while (primes[j] > i) j--;
    ip[i] = j;
  }
  while (cin >> n >> m) {
    if (n < m) {
      int temp = m;
      m = n;
      n = temp;
    }
    low_true = high_true = false;
    memset(used, 0, sizeof(used));
    search_low(m);
    if ((low_true && high_true) || !low_true)
      cout << n << endl;
    else
      cout << m << endl;
  }
  return 0;
}
