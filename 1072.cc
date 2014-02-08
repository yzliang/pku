#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Trie {
  Trie* c[26];
  bool is_word;

  Trie(): is_word(false) {
    memset(c, 0, sizeof(c));
  }

  void insert(const string& s, int start) {
    if (start == s.size()) {
      is_word = true;
    } else {
      int i = s[start] - 'A';
      if (c[i] == NULL) c[i] = new Trie;
      c[i]->insert(s, start + 1);
    }
  }
};

vector<string> words;
vector<bool> done;
Trie* root = new Trie;
char tran[256], ans[256];
bool used[256];
int num_sol;

void make_dict() {
  int d;
  cin >> d;
  for (; d > 0; d--) {
    string s;
    cin >> s;
    root->insert(s, 0);
  }
}

int chop(char* buffer) {
  static const char* sep = " \t\r\n";
  int total = 0;
  char* token = strtok(buffer, sep);
  while (token != NULL) {
    total++;
    words.push_back(token);
    token = strtok(NULL, sep);
  }
  return total;
}

void search(int p, int i, Trie* node) {
  if (i == words[p].size()) {
    if (!node->is_word) return;
    done[p] = true;
    // Pick the next word to decode.
    int min_rest = 100, next = -1;
    for (int j = 0; j < words.size(); j++) {
      if (done[j]) continue;
      int rest = words[j].size();
      for (int k = 0; k < words[j].size(); k++)
        if (tran[words[j][k]]) rest--;
      if (rest < min_rest) {
        min_rest = rest;
        next = j;
        if (min_rest == 0) break;
      }
    }
    if (next == -1) {
      // No more words, got a solution.
      num_sol++;
      if (num_sol == 1) {
        for (char c = 'A'; c <= 'Z'; c++)
          if (tran[c]) ans[tran[c]] = c;
      }
    } else
      search(next, 0, root);
    // Backtracking.
    done[p] = false;
  } else if (tran[words[p][i]]) {
    if (node->c[tran[words[p][i]] - 'A'])
      search(p, i + 1, node->c[tran[words[p][i]] - 'A']);
  } else {
    // Make a guess.
    for (char c = 'A'; c <= 'Z'; c++) {
      if (used[c] || node->c[c - 'A'] == NULL) continue;
      used[c] = true;
      tran[words[p][i]] = c;
      search(p, i + 1, node->c[c - 'A']);
      if (num_sol == 2) return;
      used[c] = false;
      tran[words[p][i]] = 0;
    }
  }
}

int main() {
  make_dict();
  int t;
  cin >> t;
  char buffer[100];
  cin.getline(buffer, 100);
  cin.getline(buffer, 100);
  for (; t > 0; t--) {
    words.clear();
    while (cin.getline(buffer, 100) && chop(buffer) != 0);
    sort(words.begin(), words.end());
    words.resize(unique(words.begin(), words.end()) - words.begin());
    done.resize(words.size());
    fill(done.begin(), done.end(), false);

    // Init and search.
    memset(tran, 0, sizeof(tran));
    memset(used, false, sizeof(used));
    num_sol = 0;
    memset(ans, 0, sizeof(ans));
    search(0, 0, root);

    switch (num_sol) {
      case 0:
        cout << "#No solution#" << endl;
        break;
      case 1:
        for (char c = 'A'; c <= 'Z'; c++)
          cout << (ans[c] ? ans[c] : '*');
        cout << endl;
        break;
      case 2:
        cout << "#More than one solution#" << endl;
        break;
    }
  }
  return 0;
}
