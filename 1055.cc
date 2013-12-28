#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int num_letters, num_bundles;
map<string, int> codes;
set<string> invalid_set;
vector<string> invalid;

bool is_valid(string& code) {
  if (code.size() != 5) return false;
  bool nonzero = false;
  for (int i = 0; i < 5; i++) {
    if (code[i] != '0') nonzero = true;
    if (!isdigit(code[i])) return false;
  }
  return nonzero;
}

void compute_bundle(int n, int& l, int& b) {
  if (n < 10) {
    l = 0;
    b = 0;
  } else if (n <= 15) {
    l = n;
    b = 1;
  } else {
    b = n / 15;
    l = b * 15;
    int rest = n % 15;
    if (rest == 0) return;
    if (b * 5 >= 10 - rest) {
      l = n;
      b++;
    }
  }
}

void find_5() {
  bool first = true;
  for (map<string, int>::iterator i = codes.begin(); i != codes.end(); i++) {
    int l, b;
    compute_bundle(i->second, l, b);
    if (b == 0) continue;
    i->second -= l;
    num_bundles += b;
    if (first) {
      first = false;
      printf("\n");
    }
    printf("%s%12d%12d\n", i->first.c_str(), l, b);
  }
}

void find_3() {
  bool first = true;
  map<string, int> code3;
  for (map<string, int>::iterator i = codes.begin(); i != codes.end(); i++)
    code3[i->first.substr(0, 3)] += i->second;
  for (map<string, int>::iterator i = code3.begin(); i != code3.end(); i++) {
    int l, b;
    compute_bundle(i->second, l, b);
    i->second = l;  // Mark the used amount.
    num_bundles += b;
    if (b > 0) {
      if (first) {
        first = false;
        printf("\n");
      }
      printf("%sxx%12d%12d\n", i->first.c_str(), l, b);
    }
  }
  // Update code map.
  for (map<string, int>::iterator i = codes.begin(); i != codes.end(); i++) {
    string prefix = i->first.substr(0, 3);
    if (code3[prefix] > i->second) {
      code3[prefix] -= i->second;
      i->second = 0;
    } else {
      i->second -= code3[prefix];
      code3[prefix] = 0;
    }
  }
}

int main() {
  string code;
  while (cin >> code) {
    if (is_valid(code)) {
      codes[code]++;
      num_letters++;
    } else if (invalid_set.find(code) == invalid_set.end()) {
      invalid_set.insert(code);
      invalid.push_back(code);
    }
  }
  printf("ZIP         LETTERS     BUNDLES\n");
  // Find 5-digit bundles.
  find_5();
  // Find 3-digit bundles.
  find_3();
  // Print first class.
  bool first = true;
  for (map<string, int>::iterator i = codes.begin(); i != codes.end(); i++) {
    if (i->second > 0) {
      if (first) {
        first = false;
        printf("\n");
      }
      printf("%s%12d%12d\n", i->first.c_str(), i->second, 0);
    }
  }
  printf("\n");
  printf("TOTALS%11d%12d\n", num_letters, num_bundles);
  // Print invalid codes.
  printf("\nINVALID ZIP CODES\n\n");
  for (int i = 0; i < invalid.size(); i++)
    printf("%s\n", invalid[i].c_str());
  return 0;
}
